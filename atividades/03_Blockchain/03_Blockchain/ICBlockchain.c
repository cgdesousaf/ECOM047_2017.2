//
//  ICBlockchain.c
//  03_Blockchain
//
//  Created by Cristopher Freitas on 3/5/18.
//  Copyright © 2018 Cristopher Freitas. All rights reserved.
//

#include "ICBlockchain.h"

void ICBlockchainCreate(ICBlockchain *_blockchain){
    // Cria uma blockchain
    blockchain.index = 0;
    
    // Cria o bloco gênesis
    ICBlock block;
    ICHash hash;
    ICHash prevHash;
    ICBlockData blockData;
    
    ICHashCreate(&hash, &blockData, &prevHash);
    
    block.data = blockData;
    block.hash = hash;
    block.previousHash = prevHash;
    
    blockchain.blocks[0] = block;
    
    _blockchain = &blockchain;
}

ICBlock * ICBlockchainGetLastBlock(ICBlockchain *blockchain){
    int index = blockchain->index;
    if(index >= 0){
        return &blockchain->blocks[index];
    } else {
        return NULL;
    }
}

ICBlock * ICBlockchainGetSingleBlock(ICBlockchain *blockchain, int index){
    int _index = blockchain->index;
    if(index <= _index){
        return &blockchain->blocks[index];
    } else {
        return NULL;
    }
}

ICBlock * ICBlockchainGetAll(ICBlockchain *blockchain){
    return blockchain->blocks;
}

bool ICBlockchainAddBlock(ICBlockchain *_blockchain, ICAddress senderAddress, ICAddress receiverAddress, int amount){
    
    // Blockchain has reached its limit
    if(blockchain.index == 99){
        return false;
    }
    
    // Get the current last block
    ICBlock currBlock;
    int index = blockchain.index;
    currBlock = blockchain.blocks[index];
    
    // Instantiate a new block
    ICBlock block;
    
    // Instantiate a new blockData
    ICBlockData blockData;
    blockData.amout = amount;
    blockData.receiverAddress = receiverAddress;
    blockData.senderAddress = senderAddress;
    
    // Generate the hash
    ICHash hash;
    ICHashCreate(&hash, &blockData, &currBlock.hash);
    
    block.data = blockData;
    block.hash = hash;
    block.previousHash = currBlock.hash;
    
    index = index + 1;
    blockchain.blocks[index] = block;
    blockchain.index = index;
    
    _blockchain = &blockchain;
    
    return true;
}

void ICBlockchainLog(ICBlockchain *blockchain){
    int size = blockchain->index + 1;
    for(int i = 0; i < size; i++){
        ICBlock block = blockchain->blocks[i];
        char * output = NULL;
        ICBlockToString(output, &block);
        printf("%s", output);
    }
}

bool ICBlockchainIsValid(ICBlockchain *blockchain){
    int index = blockchain->index;
    for(int i = index; i > 0; i--){
        ICBlock currBlock = blockchain->blocks[i];
        bool result = ICHashEquals(&currBlock.hash, &currBlock.previousHash);
        if(result == false){
            return false;
        }
    }
    return true;
}
