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

uint8_t Pixel::getComposante(int i){
    if (i>= nbrComposantes) {
        cout<<"Pixel : ce pixel n'a que "<<nbrComposantes<<" composantes (donné "<<i<<")\n";
        exit(EXIT_FAILURE);
    }
    return composantes[i];
}

GLenum Pixel::getFormat(){
    return format;
}

void Pixel::setFormat(int nbrComposantes){
    this->nbrComposantes = nbrComposantes;
    switch (nbrComposantes) {
        case 1:
            format = GL_LUMINANCE;
            break;
        case 2:
            format = GL_LUMINANCE_ALPHA;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            break;
    }
    free(composantes);
    composantes = (uint8_t*) malloc(sizeof(uint8_t)*nbrComposantes);
    for (int i = 0; i<nbrComposantes; i++) {
        composantes[i] = 0;
    }
}

void Pixel::setComposante(int indexComposante, uint8_t byte){
    if (indexComposante>=nbrComposantes) {
        cout<<"Pixel : out of composante : "<<indexComposante<<"(taille "<<nbrComposantes<<")\n";
        exit(EXIT_FAILURE);
    }
    composantes[indexComposante] = byte;
}

/* ===================================================================== */

void Image::initImage(string path){
    this->chemin = path;
    const char* filename = chemin.c_str();
    
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
        row_pointers[i] = (png_bytep)(this->texels+((this->height - (i+1))*this->width*this->nbrComposantes));
        //        row_pointers[i] = (png_bytep)(this->texels + i*this->width*this->nbrComposantes);
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

Image::Image(string path){
    initImage(path);
}

Image::Image(int width, int height, int nbrComposantes){
    this->chemin.clear();
    this->width = width;
    this->height = height;
    this->nbrComposantes = nbrComposantes;
    switch (nbrComposantes) {
        case 1:
            this->format = GL_LUMINANCE;
            break;
        case 2:
            this->format = GL_LUMINANCE_ALPHA;
            break;
        case 3:
            this->format = GL_RGB;
            break;
        case 4:
            this->format = GL_RGBA;
            break;
            
        default:
            break;
    }
    this->texels = (GLubyte *) malloc (sizeof (GLubyte) * this->width
                                       * this->height * this->nbrComposantes);
}

Image::Image(int width, int height, int nbrComposantes,string path){
    this->chemin = path;
    this->width = width;
    this->height = height;
    this->nbrComposantes = nbrComposantes;
    switch (nbrComposantes) {
        case 1:
            this->format = GL_LUMINANCE;
            break;
        case 2:
            this->format = GL_LUMINANCE_ALPHA;
            break;
        case 3:
            this->format = GL_RGB;
            break;
        case 4:
            this->format = GL_RGBA;
            break;
            
        default:
            break;
    }
    this->texels = (GLubyte *) malloc (sizeof (GLubyte) * this->width
                                       * this->height * this->nbrComposantes);
}

Image::~Image(){
    free(this->texels);
}

Pixel* Image::getPix(int x, int y){
    if (x>=width) {
        cout<<"Image : depassement de la largeur de l'image : "<<x
        <<" (taille : "<<width<<")\n";
        exit(EXIT_FAILURE);
    }
    if (y>=height) {
        cout<<"Image : depassement de la hauteur de l'image : "<<y
        <<" (taille : "<<height<<")\n";
        exit(EXIT_FAILURE);
    }
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

void Image::setPix(int x, int y, Pixel *pix){
    if (x>=width) {
        cout<<"Image : depassement de la largeur de l'image : "<<x
        <<" (taille : "<<width<<")\n";
        exit(EXIT_FAILURE);
    }
    if (y>=height) {
        cout<<"Image : depassement de la hauteur de l'image : "<<y
        <<" (taille : "<<height<<")\n";
        exit(EXIT_FAILURE);
    }
    if (pix->getFormat() != this->format) {
        cout<<"Image : format de pixel incompatible avec le format de l'image\n";
        exit(EXIT_FAILURE);
    }
    switch (format) {
        case GL_RGB:
            texels[y*width*nbrComposantes + x*nbrComposantes]=pix->getRed();
            texels[y*width*nbrComposantes + x*nbrComposantes + 1]=pix->getGreen();
            texels[y*width*nbrComposantes + x*nbrComposantes + 2]=pix->getBlue();
            break;
            
        case GL_RGBA:
            texels[y*width*nbrComposantes + x*nbrComposantes]=pix->getRed();
            texels[y*width*nbrComposantes + x*nbrComposantes + 1]=pix->getGreen();
            texels[y*width*nbrComposantes + x*nbrComposantes + 2]=pix->getBlue();
            texels[y*width*nbrComposantes + x*nbrComposantes + 3]=pix->getAlpha();
            break;
            
        case GL_LUMINANCE:
            texels[y*width*nbrComposantes + x*nbrComposantes]=pix->getGray();
            break;
            
        case GL_LUMINANCE_ALPHA:
            texels[y*width*nbrComposantes + x*nbrComposantes]=pix->getGray();
            texels[y*width*nbrComposantes + x*nbrComposantes + 1]=pix->getAlpha();
            break;
            
        default:
            cout<<"format d'image inconnu\n";
            exit(EXIT_FAILURE);
            break;
    }
}

int Image::getWidth(){
    return width;
}

int Image::getHeight(){
    return height;
}

int Image::getNbrComposantes(){
    return nbrComposantes;
}

void Image::save(){
    
    if (chemin.empty()) {
        cout<<"Image::save() le nom de l'image n'a pas été initialisé";
        exit(EXIT_FAILURE);
    }
    
    FILE * fp;
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    size_t x, y;
    png_byte ** row_pointers = NULL;
    
    int depth = 8;
    
    fp = fopen (chemin.c_str(), "wb");
    if (! fp) {
        cout<<"Image::save() ouverture du fichier impossible\n";
        throw 1;
        exit(EXIT_FAILURE);
    }
    png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
        cout<<"Image::save() initialisation du png_ptr impossible\n";
        exit(EXIT_FAILURE);
    }
    info_ptr = png_create_info_struct (png_ptr);
    if (info_ptr == NULL) {
        cout<<"Image::save() initialisation du png_info impossible\n";
        exit(EXIT_FAILURE);
    }
    if (setjmp (png_jmpbuf (png_ptr))) {
        cout<<"Image::save() truc umpossible\n";
        exit(EXIT_FAILURE);
    }
    
    int type_image;
    switch (format) {
        case GL_RGB:
            type_image = PNG_COLOR_TYPE_RGB;
            break;
        case GL_RGBA:
            type_image = PNG_COLOR_TYPE_RGBA;
            break;
        case GL_LUMINANCE:
            type_image = PNG_COLOR_TYPE_GRAY;
            break;
        case GL_LUMINANCE_ALPHA:
            type_image = PNG_COLOR_TYPE_GRAY_ALPHA;
            break;
        default:
            type_image = PNG_COLOR_TYPE_RGB;
            break;
    }
    
    png_set_IHDR (png_ptr,
                  info_ptr,
                  width,
                  height,
                  depth,
                  type_image,
                  PNG_INTERLACE_NONE,
                  PNG_COMPRESSION_TYPE_DEFAULT,
                  PNG_FILTER_TYPE_DEFAULT);
    
    /* Initialize rows of PNG. */
    
    row_pointers = (png_byte**) png_malloc (png_ptr, height * sizeof (png_byte *));
    for (y = 0; y < height; ++y) {
        png_byte *row = (png_byte*) png_malloc (png_ptr, sizeof (uint8_t) * width * nbrComposantes);
        row_pointers[y] = row;
        for (x = 0; x < width; ++x) {
            Pixel* pixel = this->getPix(x, height-1 - y);
            if (format == GL_RGB || format == GL_RGBA) {
                *row++ = pixel->getRed();
                *row++ = pixel->getGreen();
                *row++ = pixel->getBlue();
            }
            if (format == GL_LUMINANCE || format == GL_LUMINANCE_ALPHA) {
                *row++ = pixel->getGray();
            }
            if (format == GL_RGBA || format == GL_LUMINANCE_ALPHA) {
                *row++ = pixel->getAlpha();
            }
        }
    }
    
    /* PRINCIPE ACTIF */
    
    png_init_io (png_ptr, fp);
    png_set_rows (png_ptr, info_ptr, row_pointers);
    png_write_png (png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
        
    
    /* libération mémoire */
    
    for (y = 0; y < height; y++) {
        png_free (png_ptr, row_pointers[y]);
    }
    png_free (png_ptr, row_pointers);
    png_destroy_write_struct (&png_ptr, &info_ptr);
    fclose (fp);
}

void Image::write(string path){
    string tampon = chemin;
    chemin = path;
    save();
    chemin = tampon;
}

void Image::simplifier(){
    format = GL_LUMINANCE;
    
    GLubyte* newtexels = (GLubyte*) malloc(sizeof(GLubyte)*width*height);
    for (int i = 0; i<height*width; i++) {
        int tot = 0;
        for (int j = 0; j<nbrComposantes; j++) {
            tot+=texels[i*nbrComposantes + j];
        }
        newtexels[i] = tot/nbrComposantes;
    }
    free(texels);
    texels = newtexels;
    nbrComposantes = 1;
}
