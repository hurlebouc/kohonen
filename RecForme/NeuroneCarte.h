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

class NeuroneCarte {
    
private:
    
    long nbrPoids;
    double* poids;
    bool apprentit;
    InputLayer* input;
    double tempsApprentissage;
    
    void maj_poid_composante(int index, double distance);
    
public:
    static const int AMMORTISSEMENT = 0;
    static const double CONST_APPRENTISSAGE = 100;
    
    NeuroneCarte(InputLayer* input);
    double fct_transfert();
    void maj_poid(double attenuation);
    double getPoid(long indexPoid, int indexComposante);
    int getNbrComposantes();
    
};


#endif
