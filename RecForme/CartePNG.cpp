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

int CartePNG::getNumero(int x, int y){
    return y*width + x;
}

double CartePNG::distance(int i1, int i2){
    int x1 = i1 % width;
    int x2 = i2 % width;
    int y1 = i1 / width;
    int y2 = i2 / width;
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

double CartePNG::facteurAttenuationVoisin(int i1, int i2){
    double distance = this->distance(i1, i2);
//    double res = exp(-distance/(double) ((width + heigth)/10.0));
    double res = exp(-distance/(double) 2);    
    return res;
}

int* CartePNG::getVoisins(int x, int y){
    int* voisins = NULL;
    if (width == 1 || heigth == 1) {
        voisins = (int*) malloc(sizeof(int)*1);
        voisins[0] = 0;
        return voisins;
    }
    if (x == 0 && y == 0) {
        if (width == 1) {
            voisins = (int*) malloc(sizeof(int)*2);
            voisins[0] = 1;
            voisins[1] = getNumero(x, y+1);
            return voisins;
        }
        if (heigth == 1) {
            voisins = (int*) malloc(sizeof(int)*2);
            voisins[0] = 1;
            voisins[1] = getNumero(x+1, y);
            return voisins;
        }
        voisins = (int*) malloc(sizeof(int)*4);
        voisins[0] = 3;
        voisins[1] = getNumero(x, y+1);
        voisins[2] = getNumero(x+1, y);
        voisins[3] = getNumero(x+1, y+1);
        return voisins;
    }
    if (x == 0 && y == heigth-1) {
        if (width == 1) {
            voisins = (int*) malloc(sizeof(int)*2);
            voisins[0] = 1;
            voisins[1] = getNumero(x, y-1);
            return voisins;
        }
        if (heigth == 1) {
            voisins = (int*) malloc(sizeof(int)*2);
            voisins[0] = 1;
            voisins[1] = getNumero(x+1, y);
            return voisins;
        }
        voisins = (int*) malloc(sizeof(int)*4);
        voisins[0] = 3;
        voisins[1] = getNumero(x, y-1);
        voisins[2] = getNumero(x+1, y);
        voisins[3] = getNumero(x+1, y-1);
        return voisins;
    }
    if (x == width-1 &&& y == 0) {
        if (width == 1) {
            voisins = (int*) malloc(sizeof(int)*2);
            voisins[0] = 1;
            voisins[1] = getNumero(x, y+1);
            return voisins;
        }
        if (heigth == 1) {
            voisins = (int*) malloc(sizeof(int)*2);
            voisins[0] = 1;
            voisins[1] = getNumero(x-1, y);
            return voisins;
        }
        voisins = (int*) malloc(sizeof(int)*4);
        voisins[0] = 3;
        voisins[1] = getNumero(x, y+1);
        voisins[2] = getNumero(x-1, y);
        voisins[3] = getNumero(x-1, y+1);
        return voisins;
    }
    if (x == width-1 && y == heigth-1) {
        if (width == 1) {
            voisins = (int*) malloc(sizeof(int)*2);
            voisins[0] = 1;
            voisins[1] = getNumero(x, y-1);
            return voisins;
        }
        if (heigth == 1) {
            voisins = (int*) malloc(sizeof(int)*2);
            voisins[0] = 1;
            voisins[1] = getNumero(x-1, y);
            return voisins;
        }
        voisins = (int*) malloc(sizeof(int)*4);
        voisins[0] = 3;
        voisins[1] = getNumero(x, y-1);
        voisins[2] = getNumero(x-1, y);
        voisins[3] = getNumero(x-1, y-1);
        return voisins;
    }
    if (x == 0) {
        if (width == 1) {
            voisins = (int*) malloc(sizeof(int)*3);
            voisins[0] = 2;
            voisins[1] = getNumero(x, y+1);
            voisins[2] = getNumero(x, y-1);
            return voisins;
        }
        voisins = (int*) malloc(sizeof(int)*6);
        voisins[0] = 5;
        voisins[1] = getNumero(x, y+1);
        voisins[2] = getNumero(x, y-1);
        voisins[3] = getNumero(x+1, y-1);
        voisins[4] = getNumero(x+1, y);
        voisins[5] = getNumero(x+1, y+1);
        return voisins;
    }
    if (y == 0) {
        if (heigth == 1) {
            voisins = (int*) malloc(sizeof(int)*3);
            voisins[0] = 2;
            voisins[1] = getNumero(x-1, y);
            voisins[2] = getNumero(x+1, y);
            return voisins;
        }
        voisins = (int*) malloc(sizeof(int)*6);
        voisins[0] = 5;
        voisins[1] = getNumero(x-1, y);
        voisins[2] = getNumero(x+1, y);
        voisins[3] = getNumero(x+1, y+1);
        voisins[4] = getNumero(x, y+1);
        voisins[5] = getNumero(x-1, y+1);
        return voisins;
    }
    if (x == width-1) {
        if (width == 1) {
            voisins = (int*) malloc(sizeof(int)*3);
            voisins[0] = 2;
            voisins[1] = getNumero(x, y-1);
            voisins[2] = getNumero(x, y+1);
            return voisins;
        }
        voisins = (int*) malloc(sizeof(int)*6);
        voisins[0] = 5;
        voisins[1] = getNumero(x, y-1);
        voisins[2] = getNumero(x, y+1);
        voisins[3] = getNumero(x-1, y+1);
        voisins[4] = getNumero(x-1, y);
        voisins[5] = getNumero(x-1, y-1);
        return voisins;
    }
    if (y == heigth-1) {
        if (heigth == 1) {
            voisins = (int*) malloc(sizeof(int)*3);
            voisins[0] = 2;
            voisins[1] = getNumero(x+1, y);
            voisins[2] = getNumero(x-1, y);
            return voisins;
        }
        voisins = (int*) malloc(sizeof(int)*6);
        voisins[0] = 5;
        voisins[1] = getNumero(x+1, y);
        voisins[2] = getNumero(x-1, y);
        voisins[3] = getNumero(x-1, y-1);
        voisins[4] = getNumero(x, y-1);
        voisins[5] = getNumero(x+1, y-1);
        return voisins;
    }
    voisins = (int*) malloc(sizeof(int)*8);
    voisins[0] = 8;
    voisins[1] = getNumero(x-1, y-1);
    voisins[2] = getNumero(x-1, y);
    voisins[3] = getNumero(x-1, y+1);
    voisins[4] = getNumero(x, y+1);
    voisins[5] = getNumero(x+1, y+1);
    voisins[6] = getNumero(x+1, y);
    voisins[7] = getNumero(x+1, y-1);
    voisins[8] = getNumero(x, y-1);
    return voisins;
}

int* CartePNG::getVoisins(int index){
    int x = index % width;
    int y = index / width;
    return getVoisins(x, y);
}

void CartePNG::representeWithClass(char* chemin){
    Image* image = getImageWithClass();
    image->write(chemin);
    delete image;
}

Image* CartePNG::getImage(){
    InputLayerPNG* input = (InputLayerPNG*) getInputLayer();
    int nbrComposantes = input->getNbrComposantes();
    int ewidth = width*input->getWidth();
    int eheight = heigth*input->getHeight();
    Image* png = new Image(ewidth, eheight, nbrComposantes);
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
                    png->setPix(X*input->getWidth() + x,
                                Y*input->getHeight() + y,
                                pix);
                }
            }
        }
    }
    return png;
}

Image* CartePNG::getImageWithClass(){
    InputLayerPNG* input = (InputLayerPNG*) getInputLayer();
    int nbrComposantes = input->getNbrComposantes();
    int ewidth = width*input->getWidth();
    int eheight = heigth*input->getHeight();
    if (nbrComposantes == 1 || nbrComposantes == 2) {
        nbrComposantes += 2;
    }
    Image* png = new Image(ewidth, eheight, nbrComposantes);
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
                    if (estCurs(Y*width + X)) {
                        if (x<2 || x>= input->getWidth() - 2 || y<2 || y>= input->getWidth() - 2) {
                            pix->setComposante(0, 255);
                            pix->setComposante(1, 0);
                            pix->setComposante(2, 0);
                        }
                    }
                    png->setPix(X*input->getWidth() + x,
                                Y*input->getHeight() + y,
                                pix);
                }
            }
        }
    }
    return png;
}

void CartePNG::representeFrequences(char* cheminEnregistrement){
    Image* image = getImageWithFreq();
    image->write(cheminEnregistrement);
    delete image;
}

Image* CartePNG::getImageWithFreq(){
    double maxTemps = 0;
    for (int x = 0; x<width; x++) {
        for (int y = 0; y<heigth; y++) {
            double m2 = getNeurone(getNumero(x, y))->getTempsApprentissage();
            if (maxTemps<m2) {
                maxTemps=m2;
            }
        }
    }
    Image* res = new Image(width*10, heigth*10, 1);
    for (int x = 0; x<width; x++) {
        for (int y = 0; y<heigth; y++) {
            double temps = getNeurone(getNumero(x, y))->getTempsApprentissage();
            for (int i = 0; i<10; i++) {
                for (int j = 0; j<10; j++) {
                    res->setPix(x+i, y+j, new Pixel(temps/maxTemps*255));
                }
            }
        }
    }
    return res;
}






















