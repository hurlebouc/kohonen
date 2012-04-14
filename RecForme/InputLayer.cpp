//
//  InputLayer.cpp
//  RecForme
//
//  Created by Hubert Godfroy on 13/04/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

#include <iostream>
#include "InputLayer.h"

InputLayer::InputLayer(uint64_t size, int nbrComposantes){
    input = (NeuroneInput**) malloc(sizeof(NeuroneInput*)*size);
    for (uint64_t i = 0; i<size; i++) {
        input[i] = new NeuroneInput(nbrComposantes);
    }
    this->size = size;
    
}

NeuroneInput* InputLayer::getNeurone(uint64_t index){
    return input[index];
}

long InputLayer::getSize(){
    return size;
}

void InputLayer::setNeurone(uint64_t index, NeuroneInput* n){
    if (index>= size) {
        std::cout<<"InputLayer : out of boundaries : "<<index<<" (" << size << ")\n";
        exit(EXIT_FAILURE);
    }
    delete input[index];
    input[index]=n;
}

void InputLayer::setNeurone(uint64_t index, double value){
    if (index>= size) {
        std::cout<<"InputLayer : out of boundaries : "<<index<<" (" << size << ")\n";
        exit(EXIT_FAILURE);
    }
    input[index]->setValeur(value);
}

void InputLayer::setNeurone(uint64_t index, int indexComposante, double value){
    if (index>= size) {
        std::cout<<"InputLayer : out of boundaries : "<<index<<" (" << size << ")\n";
        exit(EXIT_FAILURE);
    }
    input[index]->setValeur(indexComposante, value);
}

int InputLayer::getNbrComposantes(){
    return input[0]->getNbrComposantes();
}