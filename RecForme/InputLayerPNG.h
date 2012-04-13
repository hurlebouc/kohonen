//
//  InputLayerPNG.h
//  RecForme
//
//  Created by Hubert Godfroy on 13/04/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

#ifndef RecForme_InputLayerPNG_h
#define RecForme_InputLayerPNG_h

#include "InputLayer.h"
#include "Image.h"

class InputLayerPNG : public InputLayer {
    
private:
    int width, height;
    
public:
    InputLayerPNG(int width, int height);
    InputLayerPNG(Image* png);
    NeuroneInput* getNeurone(int x, int y);    
};

#endif
