//
//  Carte.h
//  RecForme
//
//  Created by Hubert Godfroy on 11/04/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

#ifndef RecForme_Carte_h
#define RecForme_Carte_h
#include "NeuroneCarte.h"
#include "InputLayer.h"

class Carte {
    
private:
    
    /*
     * On utilisera des listes et non des tableaux pour rendre la classe plus
     * portable
     */
    
    NeuroneCarte** carte;
    InputLayer* input;
    
public:
    
    Carte(InputLayer* input, int mapsize);
    
};

#endif
