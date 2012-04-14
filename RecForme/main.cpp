//
//  main.cpp
//  RecForme
//
//  Created by Hubert Godfroy on 11/04/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

#include <iostream>
#include "Image.h"
#include "InputLayerPNG.h"
#include "CartePNG.h"

using namespace std;



int main(int argc, const char * argv[])
{
    
    Image* lena = new Image("/Users/hubert/Desktop/Lenna.png");
    cout<<"width : "<<lena->getWidth()<<" height : "<<lena->getHeight()<<"\n";
    
    Pixel* pix = lena->getPix(lena->getWidth()-1, lena->getHeight()-1);
    cout<<"rouge : "<<(int) pix->getRed()
        <<" vert : "<<(int) pix->getGreen()
        <<" bleu : "<<(int) pix->getBlue()
        <<"\n";
    
    lena->write("/Users/hubert/Desktop/Lenna2.png");
    delete pix;
    
    InputLayerPNG* input = new InputLayerPNG(lena);
    CartePNG* carte = new CartePNG(input, 2, 2);
    
    for (int i = 0; i<18; i++) {
        carte->reconnaitre();
    }
    
    carte->getImage()->save();
    
    delete lena;
    
    
    return 0;
}