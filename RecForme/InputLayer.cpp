//
//  InputLayer.cpp
//  RecForme
//
//  Created by Hubert Godfroy on 13/04/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

#include <iostream>
#include "InputLayer.h"

InputLayer::InputLayer(uint64_t size){
    input = (NeuroneInput**) malloc(sizeof(NeuroneInput*)*size);
    this->size = size;
}

NeuroneInput* InputLayer::getNeurone(uint64_t index){
    return input[index];
}

long InputLayer::getSize(){
    return size;
}