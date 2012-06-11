//
//  ClasseChiffre.h
//  RecForme
//
//  Created by Hubert Godfroy on 11/06/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

#ifndef RecForme_ClasseChiffre_h
#define RecForme_ClasseChiffre_h

#include "Classe.h"

class ClasseChiffre : public Classe{
    int nombre;
    
public:
    ClasseChiffre(int n);
    bool equals(ClasseChiffre* t);
};

#endif
