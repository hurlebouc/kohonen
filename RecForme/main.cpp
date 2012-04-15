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
    
//    Image* lena = new Image("/Users/hubert/Desktop/Lenna.png");
//    lena->simplifier();
//    lena->write("/Users/hubert/Desktop/Lenna2.png");
//    delete lena;
    
    Image* chiffre = new Image("/Volumes/Chiffres_redimensionnes/mnist_test_/2_1.png");
    chiffre->simplifier();
    cout<<chiffre->getNbrComposantes()<<"\n";
    InputLayerPNG* input = new InputLayerPNG(chiffre);
    CartePNG* carte = new CartePNG(input, 10, 10);
    
    char* snum = (char*) malloc(sizeof(char)*10);
    for (int i = 0; i<1000; i++) {
        string s = "/Volumes/Chiffres_redimensionnes/mnist_test_/";
        int num = rand()%10;
        int n = 1 + (rand()%800);
        sprintf(snum, "%d_%d.png", num, n);
        s.append(snum);
        cout<<s<<"\n";
        carte->reconnaitre();
        chiffre->initImage(s);
        chiffre->simplifier();
        input->initInputLayerPNG(chiffre);
    }
    carte->reconnaitre();
    carte->getImage()->write("/Users/hubert/Desktop/res.png");
    
    delete chiffre;
    
    
    return 0;
}