//
//  NeuroneInput.cpp
//  RecForme
//
//  Created by Hubert Godfroy on 11/04/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

#include <iostream>
#include "NeuroneInput.h"

NeuroneInput::NeuroneInput(double valeur){
    this->valeur = valeur;
}

double NeuroneInput::getValeur(){
    return valeur;
}