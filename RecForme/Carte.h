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
     * portable
     */
    
    NeuroneCarte** carte;
    InputLayer* input;
    int mapsize;
    int iteration;
    
    
    
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
    InputLayer* getInputLayer();
    
public:
    static const int ITERATION_MAX = 100;
    
    Carte(InputLayer* input, int mapsize);
    NeuroneCarte* getNeurone(int i);
    
    void reconnaitre();
};

#endif
