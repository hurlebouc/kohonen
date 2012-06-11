//
//  Carte.h
//  RecForme
//
//  Created by Hubert Godfroy on 11/04/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//
/**
 * @file Carte.h
 */

#ifndef RecForme_Carte_h
#define RecForme_Carte_h
#include "NeuroneCarte.h"
#include "InputLayer.h"

class Carte {
private:

    /*
     * On utilisera des listes et non des tableaux pour rendre la classe plus
     * universelle
     */

    NeuroneCarte** carte;
    InputLayer* input;
    int mapsize;
    int nbrCurs;
    int* tabCurs;
    int ITERATION_MAX;



    /**
     * Donne le neurone de la carte le plus proche de la couche d'entrée
     * @return 
     */
    int getPPN();

    /**
     * Modifie les poids du neurone d'index n ainsi que ceux de ces voisins.
     * @param index
     */
    void maj_neurone(int index);

    /**
     * Il faut au moins deux éléments dans le tableau
     * @param
     * @param
     * @param i index du neuone dans tabCurs
     */
    double min_dst(int i);

    /**
     * renvoie vrai si la modification est valide : dans ce cas, le tableau est 
     * modifié. Sinon non.
     * @param tabDst
     * @return 
     */
    bool updateDst(double* tabDst);
    bool estMaxLoc(int i);

protected:

    /**
     * Acces en lecture seule à la couche d'entrée du réseau
     * @return 
     */
    InputLayer* getInputLayer();
    /**
     * Renvoie un tableau comprenant l'index des curseurs
     * @return 
     */
    int* getTabCurs();

    /**
     * renvoie le nombre de curseur
     * @return 
     */
    int getNbrCurs();

    /**
     * Informe de l'état de curseur ou non d'un neurone de la carte à l'index 
     * donné.
     * @param index
     * @return 
     */
    bool estCurs(int index);

    /**
     * Donne le nombre de poids de chaques neurones de la carte.
     * @return 
     */
    uint64_t getNbrPoid();

    /* --------------------------- ABSTRACT ----------------------------- */

    /**
     * Cette méthode permet de trouver le facteur d'atténuation (qui sert à 
     * répercuter la modification des poids d'un neurone central sur ses 
     * voisins) entre deux points de la carte.
     * Cette méthode est virtuelle pure car elle dépend de la configuration des 
     * neurones de la carte.
     * @param i1
     * @param i2
     * @return 
     */
    virtual double facteurAttenuationVoisin(int i1, int i2) = 0;

    /**
     * Donne la distance entre deux neurones sur la carte
     * @param i1 index du premier neurone
     * @param i2 index du second neurone
     * @return distance entre les deux neurones
     */
    virtual double distance(int i1, int i2) = 0;

    /**
     * Donne les voisins directes d'un neurone
     * @param index index du neurone dont on souhaite connaitre les voisins
     * @return tableau d'entier dont le premier élément donne le nombre de 
     * voisins. Renvoie donc un tableau de n+1 cases si le neurone à n voisins.
     */
    virtual int* getVoisins(int index) = 0;

    /**
     * Renvoie un fichier contenant la représentation des différentes classes de
     * la carte
     * @param chemin chemin du fichier
     */
    virtual void representeWithClass(char* chemin) = 0;

    /**
     * Renvoie un fichier contenant l'ensemble des fréquences de chaque neurone
     * de la carte.
     * @param cheminEnregistrement chemin du fichier
     */
    virtual void representeFrequences(char* cheminEnregistrement) = 0;

public:


    /**
     * Constructeur d'une carte de Kohonen
     * @param input couche d'entrée du réseau
     * @param mapsize taille de la carte (nombre de neurones)
     * @param alea fonction d'aléatoire
     * @param nbrApprentissage nombre total d'apprentissage
     */
    Carte(InputLayer* input, int mapsize, AleaBox* alea, int nbrApprentissage);
    
    /**
     * Donne le neurone de la carte à l'indice i
     * @param i
     * @return 
     */
    NeuroneCarte* getNeurone(int i);
    
    /**
     * lance la procédure d'apprentissage 
     */
    void reconnaitre();
    

    void getClasses(int nbrCurs);
    void getClasses_k_means(int nbrcurs);
    
    int* getMaxLoc();
    void classify();
};

#endif
