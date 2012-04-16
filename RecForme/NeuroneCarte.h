//
//  NeuroneKohonen.h
//  RecForme
//
//  Created by Hubert Godfroy on 11/04/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

#ifndef RecForme_NeuroneKohonen_h
#define RecForme_NeuroneKohonen_h

#include "InputLayer.h"

class AleaBox {
    
public:
    virtual int aleatoire() = 0;
};

class NeuroneCarte {
    
private:
    
    long nbrPoids;
    double* poids;
    InputLayer* input;
    double tempsApprentissage;
    
    void maj_poid_numero(int index, double distance);
    
public:
    static const int AMMORTISSEMENT = 0;
    static const double CONST_APPRENTISSAGE = 100;
    
    /**
     * Contructeur permettant de choisir la classe d'entrée et la méthode d'initialisation aléatoire des neurones de la carte
     * @param input
     * @param alea
     */
    NeuroneCarte(InputLayer* input, AleaBox* alea);
    double fct_transfert();
    void maj_poid(double attenuation);
    double getPoid(long indexPoid, int indexComposante);
    int getNbrComposantes();
    
};


#endif
