//
//  InputLayer.h
//  RecForme
//
//  Created by Hubert Godfroy on 13/04/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

#ifndef RecForme_InputLayer_h
#define RecForme_InputLayer_h

#include "NeuroneInput.h"

class InputLayer {
    
private:
    long size;
    NeuroneInput** input;
    
protected:
    void setNeurone(uint64_t index, NeuroneInput* n);
    /**
     * Modifie la valeur de la première composante du neurone.
     */
    void setNeurone(uint64_t index, double value);
    void setNeurone(uint64_t index, int indexComposante, double value);
    
public:
    InputLayer(uint64_t size, int nbrComposantes);
    NeuroneInput* getNeurone(uint64_t index);
    long getSize();
    int getNbrComposantes();
};

#endif
