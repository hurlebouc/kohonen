//
//  NeuroneKohonen.cpp
//  RecForme
//
//  Created by Hubert Godfroy on 11/04/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "NeuroneCarte.h"

NeuroneCarte::NeuroneCarte(InputLayer* input) {
    this->input = input;
    nbrPoids = input->getSize();
    poids = (double*) malloc(sizeof (double) *nbrPoids);
    for (long i = 0; i < nbrPoids; i++) {
        poids[i] = rand();
    }
    apprentit = true;
    tempsApprentissage = 0;
}

double NeuroneCarte::fct_transfert() {
    double res = 0;
    for (long i = 0; i < nbrPoids; i++) {
        double val = input->getNeurone(i)->getValeur();
        res += (poids[i] - val)*(poids[i] - val);
    }
    return sqrt(res);
}

void NeuroneCarte::maj_poid(double attenuation){
    for (int i = 0; i < nbrPoids; i++) {
        this->maj_poid_composante(i, attenuation);
    }

}

void NeuroneCarte::maj_poid_composante(int index, double attenuation) {
    if (!apprentit) {
        return;
    }
    double ecart = input->getNeurone(index)->getValeur() - poids[index];
    poids[index] += ecart*exp(-tempsApprentissage/CONST_APPRENTISSAGE)*attenuation;
    tempsApprentissage += attenuation;
}