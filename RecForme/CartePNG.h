/* 
 * File:   CartePNG.h
 * Author: hubert
 *
 * Created on 14 avril 2012, 14:40
 */

#ifndef CARTEPNG_H
#define	CARTEPNG_H

#include "Carte.h"
#include "Image.h"

class AleaBoxPNG : public AleaBox {
private:
    static uint32_t t;
public:
    AleaBoxPNG();
    int aleatoire();
    
};

/* ======================================================================= */

class CartePNG : public Carte{
private:
    int width, heigth;
    int getNumero(int x, int y);
    int* getVoisins(int index);
    void representeWithClass(char* chemin);
    void representeFrequences(char* cheminEnregistrement);
    
protected:
    double facteurAttenuationVoisin(int i1, int i2);
    double distance(int i1, int i2);
    int* getVoisins(int x, int y);
    
public:
    CartePNG(InputLayer* input, int width, int height, int nbrApprentissage);
    CartePNG(Image* png, int width, int height);
    Image* getImage();
    Image* getImageWithClass();
    Image* getImageWithFreq();
};

#endif	/* CARTEPNG_H */

