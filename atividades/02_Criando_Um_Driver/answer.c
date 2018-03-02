//
//  answer.c
//  02_Criando_Um_Driver
//
//  Created by Cristopher Freitas on 2/26/18.
//  Copyright © 2018 Cristopher Freitas. All rights reserved.
//

#include "answer.h"

// Check if connection is opened, if not, open.
status_t driverOpen(uint8_t address) {
    if(!isOpened){
        status_t status = accelerometerWrite(address);
        if(status == ok){
            isOpened = 1;
        } else {
            printf("failed to open the accelerometer");
        }
        return status;
    }
    return fail;
}

// Check if connection is closed, if not, close.
status_t driverClose(uint8_t address) {
    if(isOpened){
        status_t status = accelerometerWrite(address);
        if(status == ok){
            isOpened = 0;
        } else {
            printf("failed to close the accelerometer");
        }
        return status;
    }
    return fail;
}

// Read data from the accelerometer.
status_t driverRead(uint8_t *data, uint8_t size) {
    status_t status;
    for(int i = 0; i < size; i++){
        driverOpen(ADDRESS);
        // Set the accelerometer operation to READ
        accelerometerWrite(READ_OP);
        accelerometerWrite(ACCELERATION_MODE);
        status = accelerometerRead(&data[i]);
        if(status == fail){
            printf("reading from the accelerometer failed");
            break;
        }
        driverClose(ADDRESS);
    }
    
    return status;
}

status_t driverWrite(uint8_t *data, uint8_t size) {
    status_t status;
    for(int i = 0; i < size; i++){
        driverOpen(ADDRESS);
        // Set the accelerometer operation to READ
        accelerometerWrite(WRITE_OP);
        accelerometerWrite(ACCELERATION_MODE);
        status = accelerometerWrite(data[i]);
        if(status == fail){
            printf("writing to the accelerometer failed");
            break;
        }
        driverClose(ADDRESS);
    }
    return status;
}

status_t driverIoctl(mode_t mode) {
    
    driverOpen(ADDRESS);
    accelerometerWrite(WRITE_OP);
    accelerometerWrite(SWITCH_MODE);
    status_t status = accelerometerWrite(mode);
    if(status == fail){
        printf("failed to change the accelerometer mode");
    }
    driverClose(ADDRESS);
    return status;
}

