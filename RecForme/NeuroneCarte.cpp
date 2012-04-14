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
    int nbrComposantes = input->getNbrComposantes();
    this->input = input;
    nbrPoids = input->getSize();
    poids = (double*) malloc(sizeof (double) * nbrPoids * nbrComposantes);
    for (long i = 0; i < nbrPoids*nbrComposantes; i++) {
        poids[i] = rand();
    }
    apprentit = true;
    tempsApprentissage = 0;
}

double NeuroneCarte::fct_transfert() {
    int nbrComposantes = getNbrComposantes();
    double res = 0;
    for (long i = 0; i < nbrPoids; i++) {
        for (int j = 0; j<nbrComposantes; j++) {
            double val = input->getNeurone(i)->getValeur(j);
            res += (poids[i*nbrComposantes + j] - val)*(poids[i*nbrComposantes + j] - val);
        }
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
    int nbrComposantes = getNbrComposantes();
    for (int i = 0; i<nbrComposantes; i++) {
        double ecart = input->getNeurone(index)->getValeur(i) - poids[index*nbrComposantes + i];
        poids[index*nbrComposantes + i] += ecart*exp(-AMMORTISSEMENT*tempsApprentissage/CONST_APPRENTISSAGE)*attenuation;
    }
    tempsApprentissage += attenuation;
}

double NeuroneCarte::getPoid(long indexPoid, int indexComposante){
    if (indexPoid>=nbrPoids) {
        std::cout<<"NeuroneCarte : out of poids : "<<indexPoid<<" (taille "<<nbrPoids<<"(\n";
        exit(EXIT_FAILURE);
    }
    return poids[indexPoid* getNbrComposantes() + indexComposante];
}

int NeuroneCarte::getNbrComposantes(){
    return input->getNbrComposantes();
}



