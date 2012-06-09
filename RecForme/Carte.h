//
//  Carte.h
//  RecForme
//
//  Created by Hubert Godfroy on 11/04/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

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
    // renvoie vrai si la modification est valide : dans ce cas, le tableau est 
    // modifié. Sinon non.
    bool updateDst(double* tabDst);
    
protected:
    
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
    virtual double facteurAttenuation(int i1, int i2) = 0;
    virtual double distance(int i1, int i2) = 0;
    virtual int* getVoisins(int index) = 0; // le premier élément donne le nombre de voisins
    virtual void representeWithClass(char* chemin) = 0;
    InputLayer* getInputLayer();
    int* getTabCurs();
    int getNbrCurs();
    bool estCurs(int index);
    uint64_t getNbrPoid();
    
public:
    int ITERATION_MAX;
    
    Carte(InputLayer* input, int mapsize, AleaBox* alea, int nbrApprentissage);
    NeuroneCarte* getNeurone(int i);
    void reconnaitre();
    void getClasses(int nbrCurs);
    void getClasses_k_means(int nbrcurs);
};

#endif
