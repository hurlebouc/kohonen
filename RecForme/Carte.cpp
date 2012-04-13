//
//  Carte.cpp
//  RecForme
//
//  Created by Hubert Godfroy on 11/04/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

#include <iostream>
#include "Carte.h"

Carte::Carte(InputLayer* input, int mapsize){
    carte = (NeuroneCarte**) malloc(sizeof(NeuroneCarte*)*mapsize);
    this->input = input;
}

