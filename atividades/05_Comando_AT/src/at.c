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
    // When the communication has reached its end.
    if(data == 13) {
        printk("\n");
        if((current_command.data[0] == 'A') && ( current_command.data[1] == 'T') ){
            if(current_command.data[2] == '+'){
                ATCommandInvoker(&current_command);
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

void ATCommandInvoker(struct ATCommand * command){
    printk("Calling invoker");
    uint8_t counter = 3;
    while(1){
        
        counter++;
    }
    // Iterates through command struct and find its correspondent command
}
