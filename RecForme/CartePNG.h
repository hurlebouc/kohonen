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

class CartePNG : public Carte{
private:
    int width, heigth;
    
protected:
    double facteurAttenuation(int i1, int i2);
    
public:
    CartePNG(InputLayer* input, int width, int height);
    Image* getImage();
    
};

#endif	/* CARTEPNG_H */

