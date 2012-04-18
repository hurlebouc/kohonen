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

typedef struct _curs {
    double min;
}curs;

Carte::Carte(InputLayer* input, int mapsize, AleaBox* alea, int n) {
    carte = (NeuroneCarte**) malloc(sizeof (NeuroneCarte*) * mapsize);
    this->input = input;
    this->mapsize = mapsize;
    this->iteration = 0;
    for (int i = 0; i < mapsize; i++) {
        carte[i] = new NeuroneCarte(input, alea);
    }
    ITERATION_MAX = n;

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
    //cout<<n<<"\n";
    if (iteration < ITERATION_MAX) {
        maj_neurone(n);
    }
    iteration++;
}

InputLayer* Carte::getInputLayer(){
    return input;
}

double Carte::min_dst(int *tabCurs, int taille, int n){
    double min;
    if (n == 0) {
        min = distance(tabCurs[n], tabCurs[1]);
    } else {
        min = distance(tabCurs[n], tabCurs[0]);
    }
    for (int i = 0; i<taille; i++) {
        if (i!=n) {
            double k = distance(tabCurs[n], tabCurs[i]);
            if (k<min) {
                min = k;
            }
        }
    }
    return min;
}

int* Carte::getClasses(int nbrCurs){
    
    if (nbrCurs>mapsize) {
        cout<<"Carte : on ne peut pas créer plus de classes que d'éléments dans la carte\n";
        throw 1;
    }
    int* res = (int*) malloc(sizeof(int)*nbrCurs);
    for (int i = 0; i<nbrCurs; i++) {
        bool existe = true;
        int alea;
        while (existe) {
            alea = rand()%mapsize;
            existe = false;
            for (int j = 0; j<i; j++) {
                if (alea==res[j]) {
                    existe = true;
                    break;
                }
            }
        }
        res[i] = alea;
    }
    
}
