/* 
 * File:   CartePNG.cpp
 * Author: hubert
 * 
 * Created on 14 avril 2012, 14:40
 */
#include <iostream>
#include "ctime"
#include "cmath"
#include "CartePNG.h"
#include "InputLayerPNG.h"

uint32_t AleaBoxPNG::t = 0;

AleaBoxPNG::AleaBoxPNG(){
    if (t==0) {
        t = time(NULL);
        srand(time(NULL));
        t = rand();
        srand(t);
    }
}

int AleaBoxPNG::aleatoire(){
    return rand()%255;
}

/* ======================================================================= */

CartePNG::CartePNG(InputLayer* input, int width, int height, int n)
: Carte(input, width*height, new AleaBoxPNG(), n){
    this->width = width;
    this->heigth = height;
}

double CartePNG::distance(int i1, int i2){
    int x1 = i1 % width;
    int x2 = i2 % width;
    int y1 = i1 / width;
    int y2 = i2 / width;
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

double CartePNG::facteurAttenuation(int i1, int i2){
    double distance = this->distance(i1, i2);
//    double res = exp(-distance/(double) ((width + heigth)/10.0));
    double res = exp(-distance/(double) 2);    
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