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
#include "Tests.h"

using namespace std;

int main(int argc, const char * argv[]){
    cout <<"plop\n";
    Image image("/Users/hubert/Desktop/Victorienne-gray-small.png");
    image.flouter(10);
    Filtre f(3, 3);
    f.set(0, 0, 1);
    f.set(0, 1, 2);
    f.set(0, 2, 1);
    f.set(1, 0, 2);
    f.set(1, 1, 4);
    f.set(1, 2, 2);
    f.set(2, 0, 1);
    f.set(2, 1, 2);
    f.set(2, 2, 1);
    
    Filtre f2(1,1); f2.set(0, 0, -1);
//    image.simplifier();
//    image.filtrer(&f);
    image.write("/Users/hubert/Desktop/Victorienne2.png");
    return EXIT_SUCCESS;
}


int main2(int argc, const char * argv[]){
    
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
    for (int i = 0; i<100 ; i++) {
        
        carte->reconnaitre();
        
        //nouvelle initialisation
        string s = "/Volumes/Chiffres_redimensionnes/mnist_test_/";
        int num = rand()%10;
        int n = 1 + (rand()%800);
        sprintf(snum, "%d_%d.png", num, n);
        s.append(snum);
        
        carte->initInput(s);
        
    }
    carte->reconnaitre();
    cout<<"fin de la reconnaissance\n";
    Image* i1 = carte->getImage();
    i1->write("/Users/hubert/Desktop/res.png");
    delete i1;
    Image* i2 = carte->getImageWithFreq();
    i2->write("/Users/hubert/Desktop/freq.png");
    delete i2;
    Image* i3 = carte->getImageWithClass();
    i3->write("/Users/hubert/Desktop/classe.png");
    delete i3;
    
    runTests();
    
    int* tabMax = carte->getMaxLoc();
    for (int i = 1; i<=tabMax[0]; i++) {
        cout<<tabMax[i]%10 << ", " << tabMax[i] / 10 <<"\n";
    }
    
    delete chiffre;
    
    //    CartePNG* copie = new CartePNG(i1, i2, 28, 28);
    //    copie->getImage()->write("/Users/hubert/Desktop/copie.png");
    //    copie->getImageWithFreq()->write("/Users/hubert/Desktop/copie_freq.png");
    
    return 0;
}