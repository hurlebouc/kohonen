//
//  ClasseChiffre.cpp
//  RecForme
//
//  Created by Hubert Godfroy on 11/06/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

#include <iostream>
#include "ClasseChiffre.h"

ClasseChiffre::ClasseChiffre(int n) : Classe(){
    nombre = n;
}

bool ClasseChiffre::equals(Classe *t){
    ClasseChiffre* n = (ClasseChiffre*) t;
    return n->nombre == this->nombre;
}

std::string ClasseChiffre::toString(){
    switch (nombre) {
        case 0:
            return "0";
            break;
        case 1:
            return "1";
            break;
        case 2:
            return "2";
            break;
        case 3:
            return "3";
            break;
        case 4:
            return "4";
            break;
        case 5:
            return "5";
            break;
        case 6:
            return "6";
            break;
        case 7:
            return "7";
            break;
        case 8:
            return "8";
            break;
        case 9:
            return "9";
            break;
            
        default:
            break;
    }
}