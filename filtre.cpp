//
//  filtre.cpp
//  RecForme
//
//  Created by Hubert on 11/12/2014.
//  Copyright (c) 2014 Mines de Nancy. All rights reserved.
//

#include "filtre.h"
#include <stdlib.h>

Filtre::Filtre(int w, int h) {
    if (w % 2 == 0 || h % 2 == 0) {
        printf("Filtre : les dimentions du filtres ne sont pas toutes impaires : (%ud, %ud)\n", w, h);
        exit(EXIT_FAILURE);
    }
    width = w;
    height = h;
    data = (int*) malloc(w*h*sizeof(int));
}

Filtre::~Filtre() {
    free(data);
}

void Filtre::initFlou(){
    for (int i = 0; i<width; i++) {
        for (int j = 0; j<height; j++) {
            this->set(i, j, 1);
        }
    }
}

int Filtre::get(int x, int y) {
    return data[x + y * height];
}

void Filtre::set(int x, int y, int d) {
    data[x + y * height] = d;
}

int Filtre::getDim(){
    return width;
}