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

const char* chemin = "/Users/hubert/Desktop/classement/";

typedef struct _curs {
    double min;
}curs;

Carte::Carte(InputLayer* input, int mapsize, AleaBox* alea, int n) {
    carte = (NeuroneCarte**) malloc(sizeof (NeuroneCarte*) * mapsize);
    this->input = input;
    this->mapsize = mapsize;
    for (int i = 0; i < mapsize; i++) {
        carte[i] = new NeuroneCarte(input, alea);
    }
    ITERATION_MAX = n;
    this->nbrCurs = 0;
    this->tabCurs = NULL;
}

NeuroneCarte* Carte::getNeurone(int i) {
    return this->carte[i];
}

void Carte::maj_neurone(int index) {
    for (int i = 0; i < mapsize; i++) {
        double attenuationVoisin = facteurAttenuationVoisin(index, i);
        NeuroneCarte* n = getNeurone(i);
        n->maj_poid(attenuationVoisin);
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
    if (NeuroneCarte::etapeApprentissage < ITERATION_MAX) {
        maj_neurone(n);
    }
    NeuroneCarte::etapeApprentissage++;
}

InputLayer* Carte::getInputLayer(){
    return input;
}

/* =========================== Classement ================================= */

double Carte::min_dst(int n){
    double min;
    if (n == 0) {
        min = getNeurone(tabCurs[n])->distance(getNeurone(tabCurs[1]));
    } else {
        min = getNeurone(tabCurs[n])->distance(getNeurone(tabCurs[0]));
    }
    for (int i = 0; i<nbrCurs; i++) {
        if (i!=n) {
            double k = getNeurone(tabCurs[n])->distance(getNeurone(tabCurs[i]));
            if (k<min) {
                min = k;
            }
        }
    }
    return min;
}

int* Carte::getTabCurs(){
    return tabCurs;
}

int Carte::getNbrCurs(){
    return nbrCurs;
}

uint64_t Carte::getNbrPoid(){
    return input->getSize();
}

bool Carte::estCurs(int index){
    for (int i = 0; i<nbrCurs; i++) {
        if (index == tabCurs[i]) {
            return true;
        }
    }
    return false;
}

bool Carte::updateDst(double *tabDst){
    double* tampon = (double*) malloc(sizeof(double)*nbrCurs);
    bool valide = true;
    for (int i = 0; i<nbrCurs; i++) {
        double d = min_dst(i);
        if (d<tabDst[i]) {
            valide = false;
            break;
        } else {
            tampon[i] = d;
        }
    }
    if (valide) {
        for (int i = 0; i<nbrCurs; i++) {
            tabDst[i] = tampon[i];
        }
    }
    free(tampon);
    return valide;
}

void Carte::getClasses(int nbrCurs){
    char path[1024];
    strcpy(path, chemin);
    this->nbrCurs = nbrCurs;
    if (nbrCurs>mapsize) {
        cout<<"Carte : on ne peut pas créer plus de classes que d'éléments dans la carte\n";
        throw 1;
    }
    
    /* Initialisation du tableau de curseur */
    
    if (tabCurs != NULL) {
        free(tabCurs);
    }
    tabCurs = (int*) malloc(sizeof(int)*nbrCurs);
    for (int i = 0; i<nbrCurs; i++) {
        bool existe = true;
        int alea;
        while (existe) {
            alea = rand() % mapsize;
            existe = false;
            for (int j = 0; j<i; j++) {
                if (alea==tabCurs[j]) {
                    existe = true;
                    break;
                }
            }
        }
        tabCurs[i] = alea;
    }
    
    /* Initialisation du tableau des distances */
    
    double* tabDst = (double*) malloc(sizeof(double) * nbrCurs); // à effacer
    for (int i = 0; i<nbrCurs; i++) {
        tabDst[i] = min_dst(i);
    }
    
    /* Optimisation des places de curseur */
    
    bool modification = true;
    int compteur = 0;
    while (modification) {
        compteur++;
        sprintf(path, "%simage_%d.png",chemin,compteur);
        representeWithClass(path);
        
        modification = false;
        for (int i = 0; i<nbrCurs; i++) {
            int placeini = tabCurs[i];
            int* voisins = getVoisins(placeini); // à effacer
            int bestPlace = placeini;
            double bestDst = min_dst(i);
            for (int j = 1; j<= voisins[0]; j++) {
                int newPlace = voisins[j];
                tabCurs[i] = newPlace;
                double newDst = min_dst(i);
                if (newDst > bestDst && updateDst(tabDst)) {
                    bestDst = newDst;
                    bestPlace = newPlace;
                    modification = true;
                } else {
                    tabCurs[i] = bestPlace;
                }
            }
            free(voisins);
        }
    }
    free(tabDst);
}

bool Carte::estMaxLoc(int i){
    int* tabVoisins = getVoisins(i);
    double m = getNeurone(i)->getTempsApprentissage();
    int n = tabVoisins[0];
    for (int i = 1; i<=n; i++) {
        double m2 = getNeurone(tabVoisins[i])->getTempsApprentissage();
        if (m2>m) {
            return false;
        }
    }
    return true;
}

int* Carte::getMaxLoc(){
    int* res = (int*) malloc(sizeof(int)*mapsize);
    res[0] = 0;
    for (int i = 0; i<mapsize; i++) {
        if (estMaxLoc(i)) {
            res[0]++;
            res[res[0]] = i;
        }
    }
    return res;
}


void Carte::classify(){
    int* tabMax = getMaxLoc();
    int nbrRef = tabMax[0];
    for (int i = 0; i<mapsize; i++) {
        int min = INT32_MAX;
        for (int n = 1; n<=nbrRef; n++) {
            int min2 = distance(i, tabMax[n]);
            min2 = getNeurone(i)->distance(getNeurone(tabMax[n]));
            if (min2 <= min) {
                getNeurone(i)->setIndexRef(tabMax[n]);
                min = min2;
            }
        }
    }
}
