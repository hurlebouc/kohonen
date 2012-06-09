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

int NeuroneCarte::etapeApprentissage = 0;
const double NeuroneCarte::CONST_APPRENTISSAGE = 100;

NeuroneCarte::NeuroneCarte(InputLayer* input, AleaBox* alea) {
    int nbrComposantes = input->getNbrComposantes();
    this->input = input;
    nbrPoids = input->getSize();
    poids = (double*) malloc(sizeof (double) * nbrPoids * nbrComposantes);
    for (long i = 0; i < nbrPoids*nbrComposantes; i++) {
        poids[i] = alea->aleatoire();
    }
    tempsApprentissage = 0;
}

double NeuroneCarte::fct_transfert() {
    int nbrComposantes = getNbrComposantes();
    double res = 0;
    for (long i = 0; i < nbrPoids; i++) {
        for (int j = 0; j<nbrComposantes; j++) {
            double val = input->getNeurone(i)->getComposante(j);
            res += (poids[i*nbrComposantes + j] - val)*(poids[i*nbrComposantes + j] - val);
        }
    }
    return sqrt(res);
}

void NeuroneCarte::maj_poid(double attenuationVoisin){
    for (int i = 0; i < nbrPoids; i++) {
        this->maj_poid_numero(i, attenuationVoisin);
    }
    tempsApprentissage += attenuationVoisin;
}

void NeuroneCarte::maj_poid_numero(int index, double attenuationVoisin) {
    int nbrComposantes = getNbrComposantes();
    for (int i = 0; i<nbrComposantes; i++) {
        double ecart = input->getNeurone(index)->getComposante(i) - poids[index*nbrComposantes + i];
//        poids[index*nbrComposantes + i] += ecart*exp(-AMMORTISSEMENT*tempsApprentissage/CONST_APPRENTISSAGE)*attenuationVoisin;
        poids[index*nbrComposantes + i] += ecart*exp(-AMMORTISSEMENT*etapeApprentissage/CONST_APPRENTISSAGE)*attenuationVoisin;

    }
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

double NeuroneCarte::getTempsApprentissage(){
    return tempsApprentissage;
}

/*-------------- classification ------------------*/

double NeuroneCarte::distance(NeuroneCarte *n){
    if (n->nbrPoids != this->nbrPoids) {
        std::cout<<"NeuroneCarte::distance() : les deux neurones n'ont pas le même nombre de poids\n";
        throw 1;
    }
    if (n->getNbrComposantes() != this->getNbrComposantes()) {
        std::cout<<"NeuroneCarte::distance() : les deux neurones n'ont pas le même nombre de composantes\n";
        throw 1;
    }
    double res = 0;
    for (uint64_t i = 0; i<nbrPoids; i++) {
        for (int j = 0; j<getNbrComposantes(); j++) {
            res += pow(this->getPoid(i, j) - n->getPoid(i,j), 2);
        }
    }
    return sqrt(res);
}



