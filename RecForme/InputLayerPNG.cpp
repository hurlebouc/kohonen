//
//  InputLayerPNG.cpp
//  RecForme
//
//  Created by Hubert Godfroy on 13/04/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

#include <iostream>
#include "InputLayerPNG.h"

InputLayerPNG::InputLayerPNG(int width, int height, int nbrComposantes) 
: InputLayer(width*height, nbrComposantes){
    this->width = width;
    this->height = height;
}

InputLayerPNG::InputLayerPNG(Image* png)
:InputLayer(png->getWidth()*png->getHeight(), png->getNbrComposantes()){
    this->width = png->getWidth();
    this->height = png->getHeight();
    for (int y = 0; y<height; y++) {
        for (int x = 0; x<width; x++) {
            for (int i = 0; i<png->getNbrComposantes(); i++) {
                setNeurone(y*width+x, i, png->getPix(x, y)->getComposante(i));
            }
        }
    }
}


NeuroneInput* InputLayerPNG::getNeurone(int x, int y){
    return InputLayer::getNeurone(x*y);
}

int InputLayerPNG::getWidth(){
    return width;
}

int InputLayerPNG::getHeight(){
    return height;
}