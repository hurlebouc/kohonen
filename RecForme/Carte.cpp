//
//  Carte.cpp
//  RecForme
//
//  Created by Hubert Godfroy on 11/04/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

#include <iostream>
#include "Carte.h"
using namespace std;

Carte::Carte(InputLayer* input, int mapsize, AleaBox* alea) {
    carte = (NeuroneCarte**) malloc(sizeof (NeuroneCarte*) * mapsize);
    this->input = input;
    this->mapsize = mapsize;
    this->iteration = 0;
    for (int i = 0; i < mapsize; i++) {
        carte[i] = new NeuroneCarte(input, alea);
    }

}

NeuroneCarte* Carte::getNeurone(int i) {
    return this->carte[i];
}

void Carte::maj_neurone(int index) {
    for (int i = 0; i < mapsize; i++) {
        double attenuation = facteurAttenuation(index, i);
        NeuroneCarte* n = getNeurone(i);
        n->maj_poid(attenuation);
    }
}

int Carte::getPPN() {
    int res = 0;
    int ecart = getNeurone(0)->fct_transfert();
    for (int i = 1; i < mapsize; i++) {
        NeuroneCarte* n = getNeurone(i);
        double d = n->fct_transfert();
        if (d < ecart) {
            ecart = d;
            res = i;
        }
    }

    return res;
}

void Carte::reconnaitre() {

    int n = getPPN();
    cout<<n<<"\n";
    if (iteration < ITERATION_MAX) {
        maj_neurone(n);
    }
    iteration++;
}

InputLayer* Carte::getInputLayer(){
    return input;
}
