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
    
public:
    InputLayer(uint64_t size);
    NeuroneInput* getNeurone(uint64_t index);
    long getSize();
};

#endif
