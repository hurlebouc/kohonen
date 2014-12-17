//
//  matrice.cpp
//  RecForme
//
//  Created by Hubert on 11/12/2014.
//  Copyright (c) 2014 Mines de Nancy. All rights reserved.
//

#include "matrice.h"
#include <stdlib.h>

template <typename T>
Matrice<T>::Matrice(int w, int h) {
    width = w;
    height = h;
    data = (T*) malloc(w*h*sizeof(T));
}

template <typename T>
Matrice<T>::~Matrice<T>() {
    free(data);
}

template <typename T>
T Matrice<T>::get(int i, int j) {
    return data[i + j * height];
}

template <typename T>
void Matrice<T>::set(int i, int j, T d) {
    data[i + j * height] = d;
}

template <typename T>
int Matrice<T>::getDim(){
    return width;
}

 template class Matrice<int>;
