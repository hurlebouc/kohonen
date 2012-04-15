/* 
 * File:   CartePNG.cpp
 * Author: hubert
 * 
 * Created on 14 avril 2012, 14:40
 */
#include <iostream>
#include "cmath"
#include "CartePNG.h"
#include "InputLayerPNG.h"

int AleaBoxPNG::aleatoire(){
    return rand()%255;
}

/* ======================================================================= */

CartePNG::CartePNG(InputLayer* input, int width, int height)
: Carte(input, width*height, new AleaBoxPNG()){
    this->width = width;
    this->heigth = height;
}

double CartePNG::facteurAttenuation(int i1, int i2){
    int x1 = i1 % width;
    int x2 = i2 % width;
    int y1 = i1 / width;
    int y2 = i2 / width;
    double distance = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
//    double res = exp(-distance/(double) ((width + heigth)/10.0));
    double res = exp(-distance/(double) 1);    
    return res;
}

Image* CartePNG::getImage(){
    InputLayerPNG* input = (InputLayerPNG*) getInputLayer();
    int nbrComposantes = input->getNbrComposantes();
    int ewidth = width*input->getWidth();
    int eheight = heigth*input->getHeight();
    Image* res = new Image(ewidth, eheight, nbrComposantes);
    for (int X = 0; X<width; X++) {
        for (int Y = 0; Y<heigth; Y++) {
            NeuroneCarte* n = getNeurone(Y*width + X);
            for (int x = 0; x<input->getWidth(); x++) {
                for (int y = 0; y<input->getHeight(); y++) {
                    Pixel* pix = new Pixel(0); // stub
                    pix->setFormat(nbrComposantes);
                    for (int i = 0; i<nbrComposantes; i++) {
                        uint8_t b = n->getPoid(y*input->getWidth() + x, i);
                        pix->setComposante(i, b);
                    }
                    res->setPix(X*input->getWidth() + x,
                                Y*input->getHeight() + y,
                                pix);
                }
            }
        }
    }
    return res;
}