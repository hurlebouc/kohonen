//
//  Tests.cpp
//  RecForme
//
//  Created by Hubert Godfroy on 12/06/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

#include <iostream>
#include "Tests.h"

using namespace std;

static string chemin = "/Users/hubert/Dropbox/personnel/developpeur/projet/kohonen/tests/";
static Image* map = new Image( "/Users/hubert/Dropbox/personnel/developpeur/projet/kohonen/tests/res.png");
static Image* freq = new Image("/Users/hubert/Dropbox/personnel/developpeur/projet/kohonen/tests/freq.png");
static CartePNG* carte = new CartePNG(CartePNG(map, freq, 28, 28));

static ClasseChiffre* zero = new ClasseChiffre(0);
static ClasseChiffre* un = new ClasseChiffre(1);
static ClasseChiffre* deux = new ClasseChiffre(2);
static ClasseChiffre* trois = new ClasseChiffre(3);
static ClasseChiffre* quatre = new ClasseChiffre(4);
static ClasseChiffre* cinq = new ClasseChiffre(5);
static ClasseChiffre* six = new ClasseChiffre(6);
static ClasseChiffre* sept = new ClasseChiffre(7);
static ClasseChiffre* huit = new ClasseChiffre(8);
static ClasseChiffre* neuf = new ClasseChiffre(9);

static void setTest(){
    carte->getNeurone(2,0)->setClasse(neuf);
    carte->getNeurone(5,2)->setClasse(sept);
    carte->getNeurone(9,4)->setClasse(un);
    carte->getNeurone(1,6)->setClasse(six);
    carte->getNeurone(5,8)->setClasse(cinq);
    carte->getNeurone(9,9)->setClasse(cinq);
    carte->classify();
}

void runTests(){
    char* snum = (char*) malloc(sizeof(char)*10);
    setTest();
    
    int tot = 0;
    
    for (int i = 0; i<100; i++) {
        string s = "/Volumes/Chiffres_redimensionnes/mnist_test_/";
        int num = 9;
        int n = 1 + (rand()%800);
        sprintf(snum, "%d_%d.png", num, n);
        s.append(snum);
        
        
        carte->initInput(s);
        Classe* ref = new ClasseChiffre(num);
        Classe* res = carte->getClasse();
        if (res->equals(ref)) {
            tot++;
        }
    }
    cout<<"fiabilité : "<<tot<<" \%\n";
}

