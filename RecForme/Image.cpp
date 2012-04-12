//
//  Image.cpp
//  RecForme
//
//  Created by Hubert Godfroy on 12/04/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

#include <iostream>
#include <png.h>
#include "Image.h"

using namespace std;


Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
    format = GL_RGBA;
    nbrComposantes = 4;
    composantes = (uint8_t*) malloc(4*sizeof(uint8_t));
    composantes[0] = r;
    composantes[1] = g;
    composantes[2] = b;
    composantes[3] = a;
}

Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b){
    format = GL_RGB;
    nbrComposantes = 3;
    composantes = (uint8_t*) malloc(3*sizeof(uint8_t));
    composantes[0] = r;
    composantes[1] = g;
    composantes[2] = b;
}

Pixel::Pixel(uint8_t g){
    format = GL_LUMINANCE;
    nbrComposantes = 1;
    composantes = (uint8_t*) malloc(1*sizeof(uint8_t));
    composantes[0] = g;
}

Pixel::Pixel(uint8_t g, uint8_t a){
    format = GL_LUMINANCE_ALPHA;
    nbrComposantes = 2;
    composantes = (uint8_t*) malloc(2*sizeof(uint8_t));
    composantes[0] = g;
    composantes[1] = a;
}

Pixel::~Pixel(){
    free(composantes);
}

uint8_t Pixel::getRed(){
    if (format == GL_LUMINANCE || format == GL_LUMINANCE_ALPHA) {
        cout<<"le format du pixel ne peut donner une valeur de rouge\n";
        exit(EXIT_FAILURE);
    } else {
        return composantes[0];
    }
}

uint8_t Pixel::getGreen(){
    if (format == GL_LUMINANCE || format == GL_LUMINANCE_ALPHA) {
        cout<<"le format du pixel ne peut donner une valeur de vert\n";
        exit(EXIT_FAILURE);
    } else {
        return composantes[1];
    }
}

uint8_t Pixel::getBlue(){
    if (format == GL_LUMINANCE || format == GL_LUMINANCE_ALPHA) {
        cout<<"le format du pixel ne peut donner une valeur de bleu\n";
        exit(EXIT_FAILURE);
    } else {
        return composantes[2];
    }
}

uint8_t Pixel::getAlpha(){
    if (format == GL_LUMINANCE || format == GL_RGB) {
        cout<<"le format du pixel ne peut donner une valeur de alpha\n";
        exit(EXIT_FAILURE);
    } else if (format == GL_RGBA) {
        return composantes[3];
    } else if (format == GL_LUMINANCE_ALPHA) {
        return composantes[1];
    } else {
        cout<<"format de pixel inconnu\n";
        exit(EXIT_FAILURE);
    }
}

uint8_t Pixel::getGray(){
    if (format == GL_RGBA || format == GL_RGB) {
        cout<<"le format du pixel ne peut donner une valeur de luminance\n";
        exit(EXIT_FAILURE);
    } else {
        return composantes[0];
    }
}

/* ===================================================================== */

Image::Image(const char* filename){
    
    /*
     * Ouverture et vérification du fichier
     */
    
    FILE *fp;
    png_byte magic[8];
    
    /* open image file */
    fp = fopen (filename, "rb");
    if (!fp)
    {
        fprintf (stderr, "error: couldn't open \"%s\"!\n", filename);
        exit(EXIT_FAILURE);
    }
    
    /* read magic number */
    fread (magic, 1, sizeof (magic), fp);
    
    /* check for valid magic number */
    if (!png_check_sig (magic, sizeof (magic)))
    {
        fprintf (stderr, "error: \"%s\" is not a valid PNG image!\n",
                 filename);
        fclose (fp);
        exit(EXIT_FAILURE);
    }
    
    /*
     * instensiation de png_struct et png_info
     */
    
    /* create a png read struct */
    png_structp png_ptr = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr)
    {
        fclose (fp);
        exit(EXIT_FAILURE);
    }
    
    /* create a png info struct */
    png_infop info_ptr = png_create_info_struct (png_ptr);
    if (!info_ptr)
    {
        fclose (fp);
        png_destroy_read_struct (&png_ptr, NULL, NULL);
        exit(EXIT_FAILURE);
    }
    
    /*
     * Gestion des erreurs
     */
    
    
    /* initialize the setjmp for returning properly after a libpng
     error occured */
    if (setjmp (png_jmpbuf (png_ptr)))
    {
        fclose (fp);
        png_destroy_read_struct (&png_ptr, &info_ptr, NULL);
        exit(EXIT_FAILURE);
    }
    
    /*
     *  Initialisation de la source de lecture du fichier
     */
    
    /* setup libpng for using standard C fread() function
     with our FILE pointer */
    png_init_io (png_ptr, fp);
    
    /* tell libpng that we have already read the magic number */
    png_set_sig_bytes (png_ptr, sizeof (magic));
    
    /* read png info */
    png_read_info (png_ptr, info_ptr);
    
    /*
     * Nombre de bits par pixel
     */
    
    int bit_depth, color_type;
    
    /* get some usefull information from header */
    bit_depth = png_get_bit_depth (png_ptr, info_ptr);
    color_type = png_get_color_type (png_ptr, info_ptr);
    
    /*
     * conversion des images en couleurs vraies
     */
    
    /* convert index color images to RGB images */
    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb (png_ptr);
    
    /* convert 1-2-4 bits grayscale images to 8 bits
     grayscale. */
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8 (png_ptr);
    
    if (png_get_valid (png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha (png_ptr);
    
    
    if (bit_depth == 16)
        png_set_strip_16 (png_ptr);
    else if (bit_depth < 8)
        png_set_packing (png_ptr);
    
    
    /* update info structure to apply transformations */
    png_read_update_info (png_ptr, info_ptr);
    
    
    /* retrieve updated information */
    png_get_IHDR (png_ptr, info_ptr,
                  (png_uint_32*)(&this->width),
                  (png_uint_32*)(&this->height),
                  &bit_depth, &color_type,
                  NULL, NULL, NULL);
    
    
    
    switch (color_type)
    {
        case PNG_COLOR_TYPE_GRAY:
            this->format = GL_LUMINANCE;
            this->nbrComposantes = 1;
            break;
            
        case PNG_COLOR_TYPE_GRAY_ALPHA:
            this->format = GL_LUMINANCE_ALPHA;
            this->nbrComposantes = 2;
            break;
            
        case PNG_COLOR_TYPE_RGB:
            this->format = GL_RGB;
            this->nbrComposantes = 3;
            break;
            
        case PNG_COLOR_TYPE_RGB_ALPHA:
            this->format = GL_RGBA;
            this->nbrComposantes = 4;
            break;
            
            
        default:
            /* Badness */
            break;
    }
    
    
    /* we can now allocate memory for storing pixel data */
    this->texels = (GLubyte *)malloc (sizeof (GLubyte) * this->width
                                         * this->height * this->nbrComposantes);
    
    png_bytep *row_pointers;
    
    /* setup a pointer array.  Each one points at the begening of a row. */
    row_pointers = (png_bytep *)malloc (sizeof (png_bytep) * this->height);
    
    for (int i = 0; i < this->height; ++i)
    {
        row_pointers[i] = (png_bytep)(this->texels +
                                      ((this->height - (i + 1)) * this->width * this->nbrComposantes));
    }
    
    /* read pixel data using row pointers */
    png_read_image (png_ptr, row_pointers);
    
    /* we don't need row pointers anymore */
    free (row_pointers);
    
    
    /* finish decompression and release memory */
    png_read_end (png_ptr, NULL);
    png_destroy_read_struct (&png_ptr, &info_ptr, NULL);
    
    fclose (fp);
}

Image::Image(int width, int height){
    this->width = width;
    this->height = height;
    this->format = GL_RGB;
    this->nbrComposantes = 3;
    this->texels = (GLubyte *) malloc (sizeof (GLubyte) * this->width
                                      * this->height * this->nbrComposantes);
}

Image::~Image(){
    free(this->texels);
}

Pixel* Image::getPix(int x, int y){
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
    switch (format) {
        case GL_RGB:
            r = texels[y*width*nbrComposantes + x*nbrComposantes];
            g = texels[y*width*nbrComposantes + x*nbrComposantes + 1];
            b = texels[y*width*nbrComposantes + x*nbrComposantes + 2];
            return new Pixel(r, g, b);
            break;
            
        case GL_RGBA:
            r = texels[y*width*nbrComposantes + x*nbrComposantes];
            g = texels[y*width*nbrComposantes + x*nbrComposantes + 1];
            b = texels[y*width*nbrComposantes + x*nbrComposantes + 2];
            a = texels[y*width*nbrComposantes + x*nbrComposantes + 3];
            return new Pixel(r, g, b, a);
            break;
            
        case GL_LUMINANCE:
            g = texels[y*width*nbrComposantes + x*nbrComposantes];
            return new Pixel(g);
            break;
            
        case GL_LUMINANCE_ALPHA:
            g = texels[y*width*nbrComposantes + x*nbrComposantes];
            a = texels[y*width*nbrComposantes + x*nbrComposantes + 1];
            return new Pixel(g, a);
            break;
            
        default:
            cout<<"format d'image inconnu\n";
            exit(EXIT_FAILURE);
            break;
    }
}









