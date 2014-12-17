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

//#define GL_ALPHA                          0x1906
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908
#define GL_LUMINANCE                      0x1909
#define GL_LUMINANCE_ALPHA                0x190A
#include "filtre.h"

//#include <GL/gl.h>

typedef unsigned int    format_t;       // GLenum
typedef int             composante_t;   // GLint
typedef unsigned int    taille_t;       // GLuint
typedef unsigned char   byte_t;         // GLubyte


class Pixel {
    
private:
    format_t  format;          /* RVB, RVBA, Luminance, Luminance Alpha */
    composante_t   nbrComposantes;  /* composantes d'un texel */
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
    format_t getFormat();
    
    /**
     * Donne la composante de rouge d'un pixel
     * @return 
     */
    uint8_t getRed();
    
    /**
     * Change la composante de rouge d'un pixel
     * @param composante rouge
     */
    void setRed(byte_t);
    
    /**
     * Donne la composante de vert d'un pixel
     * @return 
     */
    uint8_t getGreen();
    
    /**
     * Change la composante de vert d'un pixel
     * @param composante verte
     */
    void setGreen(byte_t);
    
    /**
     * Donne la composante de bleu d'un pixel
     * @return 
     */
    uint8_t getBlue();
    
    /**
     * Change la composante de bleu d'un pixel
     * @param composante bleue
     */
    void setBlue(byte_t);
    
    /**
     * Donne la composante alpha d'un pixel
     * @return 
     */
    uint8_t getAlpha();
    
    /**
     * Change la composante de alpha d'un pixel
     * @param composante alpha
     */
    void setAlpha(byte_t);
    
    /**
     * Donne la composante de gris d'un pixel
     * @return 
     */
    uint8_t getGray();
    
    /**
     * Change la composante de gris d'un pixel
     * @param composante grise
     */
    void setGray(byte_t);
    
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
    taille_t  width;           /* largeur */
    taille_t  height;          /* hauteur */
    format_t  format;          /* RVB, RVBA, Luminance, Luminance Alpha */
    composante_t   nbrComposantes;  /* composantes d'un texel */
    byte_t *texels;         /* données de l'image */
    
    void flouterRGB(int);
    void flouterRGBA(int);
    void flouterG(int);
    void flouterGA(int);
    composante_t getNbrVisibleComp();
    
public:
    
    Image(std::string path);
    Image(int width, int height, int nbrComposantes);
    Image(int width, int height,  int nbrComposantes, std::string path);
    ~Image();
    
    void initImage(std::string path);
    Pixel getPix(int x, int y); // *nouveau* pixel (copy)
    void setPix(int x, int y, Pixel &pix);
    int getWidth();
    int getHeight();
    int getNbrComposantes();
    void save();
    void write(std::string path);
    void simplifier();
    void removeAlfa();
    
    /**
     * Autant de filtres que de composantes (au moins)
     * Filtre de taille impaire
     * Dans l'ordre RGBA ou GA
     */
    void filtrerParComposante(Filtre*[]);
    
    void filtrer(Filtre*);

    
    /**
     * FLoute la photo
     * @param r rayon de floutage
     */
    void flouter(int r);
    void deriver(int r);
};

#endif
