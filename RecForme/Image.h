//
//  Image.h
//  RecForme
//
//  Created by Hubert Godfroy on 12/04/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//
//  Cette classe utilise la bibliothèque libpng et openGL
//

#ifndef RecForme_Image_h
#define RecForme_Image_h

#include <GL/gl.h>

class Pixel {
    
private:
    GLenum  format;          /* RVB, RVBA, Luminance, Luminance Alpha */
    GLint   nbrComposantes;  /* composantes d'un texel */
    uint8_t* composantes;
    
public:
    Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    Pixel(uint8_t r, uint8_t g, uint8_t b);
    Pixel(uint8_t g);
    Pixel(uint8_t g, uint8_t a);
    ~Pixel();
    
    uint8_t getRed();
    uint8_t getGreen();
    uint8_t getBlue();
    uint8_t getAlpha();
    uint8_t getGray();
};

/* ===================================================================== */

class Image {
    
private:
    
    GLuint  width;           /* largeur */
    GLuint  height;          /* hauteur */
    GLenum  format;          /* RVB, RVBA, Luminance, Luminance Alpha */
    GLint   nbrComposantes;  /* composantes d'un texel */
    GLubyte *texels;         /* données de l'image */
    
public:
    
    Image(const char* path);
    Image(int width, int height);
    ~Image();
    
    Pixel* getPix(int x, int y);
};

#endif
