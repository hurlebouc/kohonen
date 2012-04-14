//
//  NeuroneInput.cpp
//  RecForme
//
//  Created by Hubert Godfroy on 11/04/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

#include <iostream>
#include "NeuroneInput.h"

NeuroneInput::NeuroneInput(int nbrComposantes){
    this->nbrComposantes = nbrComposantes;
    this->composantes = (int*) malloc(sizeof(int)*nbrComposantes);
    for (int i = 0; i<nbrComposantes; i++) {
        composantes[i] = 0;
    }
}

//double NeuroneInput::getValeur(){
//    return composantes[0];
//}

double NeuroneInput::getValeur(int index){
    if (index>= nbrComposantes) {
        std::cout<<"NeuroneInput : out of boundaries : "<<index<<" ("<<nbrComposantes<<")";
        exit(EXIT_FAILURE);
    }
    return composantes[index];
}

void NeuroneInput::setValeur(double v){
    composantes[0] = v;
}

void NeuroneInput::setValeur(int index, double v){
    if (index>= nbrComposantes) {
        std::cout<<"NeuroneInput : out of boundaries : "<<index<<" (taille "<<nbrComposantes<<")";
        exit(EXIT_FAILURE);
    }
    composantes[index] = v;
}

int NeuroneInput::getNbrComposantes(){
    return nbrComposantes;
}