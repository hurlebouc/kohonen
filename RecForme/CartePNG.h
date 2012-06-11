/** 
 * @file:   CartePNG.h
 * @author: hubert
 *
 * Created on 14 avril 2012, 14:40
 */

#ifndef CARTEPNG_H
#define	CARTEPNG_H

#include "Carte.h"
#include "Image.h"

class AleaBoxPNG : public AleaBox {
private:
    static uint32_t t;
public:
    AleaBoxPNG();
    int aleatoire();

};

/* ======================================================================= */

class CartePNG : public Carte {
private:
    int width, heigth;
    /**
     * Donne l'index dans la classe Carte du neurone de coordonnée x et y
     * @param x
     * @param y
     * @return 
     */
    int getNumero(int x, int y);
    
    void representeWithClass(char* chemin);
    void representeFrequences(char* cheminEnregistrement);

protected:
    double facteurAttenuationVoisin(int i1, int i2);
    double distance(int i1, int i2);
    int* getVoisins(int index);
    /**
     * Donne les voisins directs du neurone à la place (x,y)
     * @param x
     * @param y
     * @return 
     */
    int* getVoisins(int x, int y);

public:

    /**
     * Constructeur de la carte
     * @param input
     * @param width
     * @param height
     * @param nbrApprentissage
     */
    CartePNG(InputLayer* input, int width, int height, int nbrApprentissage);

    /**
     * Construction d'une carte à partir d'une image
     * @param png
     * @param width
     * @param height
     * @param nbrApprentissage
     */
    CartePNG(Image* png, int width, int height, int nbrApprentissage);

    /**
     * Renvoie une image de la carte
     * @return 
     */
    Image* getImage();

    /**
     * Renvoie une image de la carte sur laquelle sont ajouté les neurones de 
     * référence de chaque classe
     * @return 
     */
    Image* getImageWithClass();
    /**
     * Donne une image représentant les fréquences d'utilisation de chaque de 
     * la carte
     * @return 
     */
    Image* getImageWithFreq();
    
    NeuroneCarte* getNeurone(int x);
    NeuroneCarte* getNeurone(int x, int y);
    
};

#endif	/* CARTEPNG_H */

