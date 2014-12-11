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
    width = w;
    height = h;
    data = (int*) malloc(w*h*sizeof(int));
}

Filtre::~Filtre() {
    free(data);
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