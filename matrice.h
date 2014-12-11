//
//  matrice.h
//  RecForme
//
//  Created by Hubert on 11/12/2014.
//  Copyright (c) 2014 Mines de Nancy. All rights reserved.
//

#ifndef __RecForme__matrice__
#define __RecForme__matrice__

#include <stdio.h>

template <typename T>
class Matrice {
    
private:
    T* data;
    int width;
    int height;
    
public:
    Matrice(int w, int h);
    ~Matrice();
    T get(int i, int j);
    void set(int i, int j, T d);
    int getDim();
    
};

#endif /* defined(__RecForme__matrice__) */
