//
//  ICBlockchain.h
//  03_Blockchain
//
//  Created by Cristopher Freitas on 3/5/18.
//  Copyright © 2018 Cristopher Freitas. All rights reserved.
//

#ifndef icblockchain_h
#define icblockchain_h

#include "ICBlock.h"

#define BLOCKCHAIN_MAX_SIZE 100

struct ICBlockchain {
    ICBlock blocks[BLOCKCHAIN_MAX_SIZE];
    int index;
}; typedef struct ICBlockchain ICBlockchain;

static ICBlockchain blockchain;

void ICBlockchainCreate(ICBlockchain *blockchain);
ICBlock * ICBlockchainGetLastBlock(ICBlockchain *blockchain);
ICBlock * ICBlockchainGetSingleBlock(ICBlockchain *blockchain, int index);
ICBlock * ICBlockchainGetAll(ICBlockchain *blockchain);
bool ICBlockchainAddBlock(ICBlockchain *blockchain, ICAddress senderAddress, ICAddress receiverAddress, int amount);
void ICBlockchainLog(ICBlockchain *blockchain);
bool ICBlockchainIsValid(ICBlockchain *blockchain);

#endif
