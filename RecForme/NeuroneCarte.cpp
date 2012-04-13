//
//  NeuroneKohonen.cpp
//  RecForme
//
//  Created by Hubert Godfroy on 11/04/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

#include <iostream>
#include "NeuroneCarte.h"

NeuroneCarte::NeuroneCarte(InputLayer* input){
    this->input = input;
    dim = input->getSize();
    poids = (double*) malloc(sizeof(double)*dim);
    for (long i = 0; i<dim; i++) {
        poids[i] = rand();
    }
    apprentit = true;
}

double NeuroneCarte::fct_transfert(){
    double res = 0;
    for (long i = 0; i<dim; i++) {
        res += (poids[i] - input->getNeurone(i)->getValeur());
        maj_poid(i);
    }
    return res;
}

void NeuroneCarte::maj_poid(int index){
    
}