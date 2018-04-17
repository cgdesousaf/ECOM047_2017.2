//
//  at.c
//  
//
//  Created by Cristopher Freitas on 4/12/18.
//

#include "at.h"

static struct ATCommand current_command = {};

const struct ATCommandStruct ATCommands[] = {
    {"Test", &ATTestCommunication, 0, ""},
    {"Init", &IC_LED_matrix_init, 0, ""},
    {"DrawHeart", &IC_LED_matrix_draw_heart, 0, ""},
    {"SetTime", &IC_LED_matrix_set_time_active, 1, "int"},
    {"DrawHours", &IC_LED_matrix_draw_hours, 2, "int,int"},
    {"DrawString", &IC_LED_matrix_draw_string, 1, "string"},
    {"DrawName", &IC_LED_matrix_draw_name, 2, "string,string"},
    {"DrawDate", &IC_LED_matrix_draw_date, 4, "int,string,int,int"},
    {"", 0, 0, {""}} // End of struct
};

void ATCommandInit(struct ATCommand * command){
    for(uint8_t i = 0; i < MAX_CMD_LEN; i++){
        command->data[i] = 0;
    }
    command->index = 0;
}

void ATCommandPush(struct ATCommand * command, uint8_t data){
    command->data[command->index] = data;
    command->index++;
}

int ATTestCommunication(void){
    printk("\nOK\n");
    return 0;
}

void ATCommandParser(uint8_t data){
    // When the ENTER has been pressed.
    if(data == 13) {
        printk("\n");
        if((current_command.data[0] == 'A') && ( current_command.data[1] == 'T') ){
            if(current_command.data[2] == '+'){
                uint8_t command_name[10] = {0};
                uint8_t command_len = 0;
                for(uint8_t i = 0; i < 10; i++){
                    // Check if the command string has ended or if it doesn't exist one.
                    if((current_command.data[i+3] == '=') || (current_command.data[i+3] == '\0')){
                        break;
                    }
                    command_name[i] = current_command.data[i+3];
                    command_len++;
                }
                ATCommandInvoker(command_name, command_len);
            } else {
                ATTestCommunication();
                ATCommandInit(&current_command);
            }
        } else {
            printk("\nFAIL\n");
            ATCommandInit(&current_command);
        }
    } else {
        ATCommandPush(&current_command, data);
        printk("%c", data);
    }
}

void ATCommandInvoker(uint8_t * command_name, uint8_t command_len){
    uint8_t command_index = 0;
    struct ATCommandStruct local_command = ATCommands[command_index];
    
    // Find the adequate command.
    do {
        // Compare command name to existing commands
        if(strcmp(local_command.name, command_name) == 0){
            break;
        }
        // If command struct has reached its end without matching any command.
        else if(strcmp(local_command.name, "") == 0) {
            printk("\nFAIL\n");
            ATCommandInit(&current_command);
            return;
        }
        // Try another.
        else {
            command_index++;
            local_command = ATCommands[command_index];
        }
    } while(1);
    
    // Execute the command.
    uint8_t data_index = 3 + command_len + 1;

    // Get params array
    uint8_t * params[(int)local_command.num_params];

//    uint8_t * types[(int)local_command.num_params] = parseTypes(local_command.types);

//    for(uint8_t i = 0; i < local_command.num_params; i++){
//        // Check param type
//    }

    local_command.execute(params, local_command.num_params);
    printk("\nOK\n");

    // Restart communication
    ATCommandInit(&current_command);
    return;
}
