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

bool ClasseChiffre::equals(ClasseChiffre *t){
    return t->nombre == this->nombre;
}