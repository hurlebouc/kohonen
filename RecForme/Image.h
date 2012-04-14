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
    
    GLenum getFormat();
    uint8_t getRed();
    uint8_t getGreen();
    uint8_t getBlue();
    uint8_t getAlpha();
    uint8_t getGray();
    uint8_t getComposante(int i);
    void setFormat(int nbrComposantes);
    void setComposante(int indexComposante, uint8_t byte);
};

/* ===================================================================== */

class Image {
    
private:
    std::string chemin;
    GLuint  width;           /* largeur */
    GLuint  height;          /* hauteur */
    GLenum  format;          /* RVB, RVBA, Luminance, Luminance Alpha */
    GLint   nbrComposantes;  /* composantes d'un texel */
    GLubyte *texels;         /* données de l'image */
    
public:
    
    Image(std::string path);
    Image(int width, int height);
    Image(int width, int height, std::string path);
    ~Image();
    
    Pixel* getPix(int x, int y);
    void setPix(int x, int y, Pixel* pix);
    int getWidth();
    int getHeight();
    int getNbrComposantes();
    void save();
    void write(std::string path);
};

#endif
