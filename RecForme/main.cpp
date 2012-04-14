//
//  main.cpp
//  RecForme
//
//  Created by Hubert Godfroy on 11/04/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

#include <iostream>
#include "Image.h"

using namespace std;



int main(int argc, const char * argv[])
{
    
    Image* lena = new Image("/Users/hubert/Desktop/Lenna.png");
    cout<<"width : "<<lena->getWidth()<<" height : "<<lena->getHeight()<<"\n";
    
    Pixel* pix = lena->getPix(lena->getWidth()-1, lena->getHeight()-1);
    cout<<"rouge : "<<(int) pix->getRed()
        <<" vert : "<<(int) pix->getGreen()
        <<" bleu : "<<(int) pix->getBlue();
    
    lena->write("/Users/hubert/Desktop/Lenna2.png");
    delete lena;
    delete pix;
    
    return 0;
}