//
//  at.h
//  
//
//  Created by Cristopher Freitas on 4/12/18.
//

#ifndef at_h
#define at_h

#include "ICLEDMatrix.h"

#define ASCII_TO_INT(x) x - '0'

#define MAX_CMD_LEN 128

typedef int(*functionPointerType)(const uint8_t **, const uint8_t);

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

void ATCommandInvoker(uint8_t * command_name, uint8_t command_len);
void ATCommandParser(uint8_t data);

int ATTestCommunication();

#endif /* at_h */
