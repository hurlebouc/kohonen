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
    /**
     * Constructeur d'un pixel ayant 4 composantes
     * @param r
     * @param g
     * @param b
     * @param a
     */
    Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    
    /**
     * Constructeur d'un pixel ayant 3 composantes
     * @param r
     * @param g
     * @param b
     */
    Pixel(uint8_t r, uint8_t g, uint8_t b);
    
    /**
     * Constructeur d'un pixel ayant 1 composante
     * @param g
     */
    Pixel(uint8_t g);
    
    /**
     * Constructeur d'un pixel ayant 2 composantes
     * @param g
     * @param a
     */
    Pixel(uint8_t g, uint8_t a);
    
    /**
     * Destructeur d'un pixel
     */
    ~Pixel();
    
    /**
     * Donne le format d'un pixel
     * @return 
     */
    GLenum getFormat();
    
    /**
     * Donne la composante de rouge d'un pixel
     * @return 
     */
    uint8_t getRed();
    
    /**
     * Donne la composante de vert d'un pixel
     * @return 
     */
    uint8_t getGreen();
    
    /**
     * Donne la composante de bleu d'un pixel
     * @return 
     */
    uint8_t getBlue();
    
    /**
     * Donne la composante alpha d'un pixel
     * @return 
     */
    uint8_t getAlpha();
    
    /**
     * Donne la composante de gris d'un pixel
     * @return 
     */
    uint8_t getGray();
    
    /**
     * Donne la composante numéro i d'un pixel
     * @param i
     * @return 
     */
    uint8_t getComposante(int i);
    
    /**
     * Formate un pixel
     * @param nbrComposantes
     */
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
    Image(int width, int height, int nbrComposantes);
    Image(int width, int height,  int nbrComposantes, std::string path);
    ~Image();
    
    void initImage(std::string path);
    Pixel* getPix(int x, int y);
    void setPix(int x, int y, Pixel* pix);
    int getWidth();
    int getHeight();
    int getNbrComposantes();
    void save();
    void write(std::string path);
    void simplifier();
};

#endif
