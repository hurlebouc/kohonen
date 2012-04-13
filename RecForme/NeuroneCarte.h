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
    
    long dim;
    double* poids;
    bool apprentit;
    InputLayer* input;
    
    void maj_poid(int index);
    
public:
    NeuroneCarte(InputLayer* input);
    double fct_transfert();
    
};


#endif
