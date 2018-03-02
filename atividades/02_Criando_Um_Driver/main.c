//
//  main.c
//  02_Criando_Um_Driver
//
//  Created by Cristopher Freitas on 2/26/18.
//  Copyright © 2018 Cristopher Freitas. All rights reserved.
//

#include <stdio.h>
#include "answer.h"

int main() {
    uint8_t size = 10;
    uint8_t buffer[size];
    driverIoctl(runMode);
    driverRead(buffer, size);
    
    for (int i = 0; i < size; i++) {
        printf("reading: %d\n", buffer[i]);
    }
    
    uint8_t data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    driverWrite(data, size);
    
    return 0;
}

