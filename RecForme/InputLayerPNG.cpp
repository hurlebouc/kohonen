//
//  InputLayerPNG.cpp
//  RecForme
//
//  Created by Hubert Godfroy on 13/04/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

#include <iostream>
#include "InputLayerPNG.h"

InputLayerPNG::InputLayerPNG(int width, int height) 
: InputLayer(width*height){
    this->width = width;
    this->height = height;
}

InputLayerPNG::InputLayerPNG(Image* png)
:InputLayer(png->getWidth()*png->getHeight()){
    this->width = png->getWidth();
    this->height = png->getHeight();
}


NeuroneInput* InputLayerPNG::getNeurone(int x, int y){
    return InputLayer::getNeurone(x*y);
}