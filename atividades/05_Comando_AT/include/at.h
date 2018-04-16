//
//  at.h
//  
//
//  Created by Cristopher Freitas on 4/12/18.
//

#ifndef at_h
#define at_h

#include <zephyr.h>
#include <misc/printk.h>
#include <board.h>
#include <gpio.h>
#include <device.h>
#include <stdio.h>
#include <string.h>

#define MAX_CMD_LEN 128

typedef void(*functionPointerType)(void);

struct ATCommand {
    uint8_t data[MAX_CMD_LEN];
    uint8_t index;
};

void ATCommandInit(struct ATCommand * command);
void ATCommandPush(struct ATCommand * command, uint8_t data);

struct ATCommandStruct {
    char const *name;
    functionPointerType execute;
    uint8_t *num_params;
    char const *types;
};

void ATCommandInvoker(struct ATCommand * command, const char * command_name, uint8_t command_len);
void ATCommandParser(uint8_t data);

void ATTestCommunication();

#endif /* at_h */
