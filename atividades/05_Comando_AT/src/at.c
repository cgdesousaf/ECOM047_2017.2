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
    {"", 0, 0, ""} // End of struct
};

void ATCommandInit(struct ATCommand * command){
    command->index = 0;
}

void ATCommandPush(struct ATCommand * command, uint8_t data){
    command->data[command->index] = data;
    command->index++;
}

void ATTestCommunication(){
    printk("\nCommunication is working\n");
}

void ATCommandParser(uint8_t data){
    // When the ENTER has been pressed.
    if(data == 13) {
        printk("\n");
        if((current_command.data[0] == 'A') && ( current_command.data[1] == 'T') ){
            if(current_command.data[2] == '+'){
                char command_name[10];
                uint8_t command_len = 0;
                for(uint8_t i = 0; i < 10; i++){
                    // Check if the command string has ended or if it doesn't exist one.
                    if((current_command.data[i+3] == '=') || (current_command.data[i+3] == '\0')){
                        break;
                    }
                    command_name[i] = current_command.data[i+3];
                    command_len++;
                }
                ATCommandInvoker(&current_command, command_name, command_len);
            } else {
                ATTestCommunication();
                ATCommandInit(&current_command);
            }
        } else {
            printk("\nInvalid Command\n");
        }
    } else {
        ATCommandPush(&current_command, data);
        printk("%c", data);
    }
}

void ATCommandInvoker(struct ATCommand * command, const char * command_name, uint8_t command_len){
    printk("\nCalling invoker\n");
    sprintk("Command: %s", command_name);
    
    uint8_t data_index = 3 + command_len;
    
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
            printk("\nCommand not found\n");
            return;
        }
        // Try another.
        else {
            command_index++;
            local_command = ATCommands[command_index];
        }
    } while(1);
    
    // Execute the command.
    printk("\nExecuting command\n");
}
