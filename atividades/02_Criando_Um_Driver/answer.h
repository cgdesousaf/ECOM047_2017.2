//
//  answer.h
//  02_Criando_Um_Driver
//
//  Created by Cristopher Freitas on 2/26/18.
//  Copyright © 2018 Cristopher Freitas. All rights reserved.
//

#ifndef answer_h
#define answer_h

#include <stdio.h>
#include "types.h"
#include "accelerometer.h"

/* Operations bytecode */

#define ADDRESS 0xE3
#define READ_OP 0x21
#define WRITE_OP 0x31
#define SWITCH_MODE 0xB3
#define ACCELERATION_MODE 0xC3

/* Driver functions */

status_t driverOpen(uint8_t address);
status_t driverClose(uint8_t address);
status_t driverRead(uint8_t *data, uint8_t size);
status_t driverWrite(uint8_t *data, uint8_t size);
status_t driverIoctl(mode_t mode);

static int isOpened = 0;

#endif /* answer_h */
