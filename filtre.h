//
//  filtre.h
//  RecForme
//
//  Created by Hubert on 11/12/2014.
//  Copyright (c) 2014 Mines de Nancy. All rights reserved.
//

/**
 
 ^
 |
y|
 |
 ---------->
    x
 */

#ifndef __RecForme__filtre__
#define __RecForme__filtre__

#include <stdio.h>

class Filtre{
    
private:
    int* data;
    int width;
    int height;
    
public:
    Filtre(int w, int h);
    ~Filtre();
    int get(int x, int y);
    void set(int x, int y, int d);
    int getDim();
    void initFlou();
};

#endif /* defined(__RecForme__filtre__) */
