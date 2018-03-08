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
    int size;
} typedef ICBlockchain ICBlockchain;

static ICBlockchain blockchain;

void ICBlockchainCreate(ICBlockchain *blockchain);
int ICBlockchainGetLastBlock(ICBlockchain *blockchain);
int ICBlockchainGetSingleBlock(ICBlockchain *blockchain, ICBlock *block, int index);
ICBlock[] * ICBlockchainGetAll(ICBlockchain *blockchain);
int ICBlockchainAddBlock(ICBlockchain *blockchain, ICAddress senderAddress, ICAddress receiverAddress, int amout);
void ICBlockchainLog(ICBlockchain *blockchain);
int ICBlockchainIsValid(ICBlockchain *blockchain);


