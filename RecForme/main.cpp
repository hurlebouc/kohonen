//
//  main.cpp
//  RecForme
//
//  Created by Hubert Godfroy on 11/04/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

#include <iostream>
#include <ctime>
#include "Image.h"
#include "InputLayerPNG.h"
#include "CartePNG.h"

using namespace std;



int main(int argc, const char * argv[]){
    
    uint32_t t = time(NULL);
    srand(time(NULL));
    t = rand();
    srand(t);
    
    Image* chiffre = new Image("/Volumes/Chiffres_redimensionnes/mnist_test_/2_1.png");
    chiffre->simplifier();
    cout<<chiffre->getNbrComposantes()<<"\n";
    InputLayerPNG* input = new InputLayerPNG(chiffre);
    CartePNG* carte = new CartePNG(input, 10, 10, INT32_MAX);
    
    char* snum = (char*) malloc(sizeof(char)*10);
    for (int i = 0; i<1000 ; i++) {
        string s = "/Volumes/Chiffres_redimensionnes/mnist_test_/";
        int num = rand()%10;
        int n = 1 + (rand()%800);
        sprintf(snum, "%d_%d.png", num, n);
        s.append(snum);
        //cout<<s<<"\n";
        carte->reconnaitre();
        
        //nouvelle initialisation
        chiffre->initImage(s);
        chiffre->simplifier();
        input->initInputLayerPNG(chiffre);
    }
    carte->reconnaitre();
    cout<<"fin de la reconnaissance\n";
//    carte->getClasses(10);
    cout<<"fin du classement\n";
    carte->getImage()->write("/Users/hubert/Desktop/res.png");
//    carte->getImageWithClass()->write("/Users/hubert/Desktop/res.png");
    carte->getImageWithFreq()->write("/Users/hubert/Desktop/freq.png");
    int* tabMax = carte->getMaxLoc();
    for (int i = 1; i<=tabMax[0]; i++) {
        cout<<tabMax[i]%10 << ", " << tabMax[i] / 10 <<"\n";
    }
    
    delete chiffre;
    
    
    return 0;
}