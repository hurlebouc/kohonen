//
//  NeuroneInput.h
//  RecForme
//
//  Created by Hubert Godfroy on 11/04/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//


#ifndef RecForme_NeuroneInput_h
#define RecForme_NeuroneInput_h

class NeuroneInput {
    
private:
    int nbrComposantes;
    int* composantes;
    
public:
    NeuroneInput(int nbrComposantes);
    
    double getComposante(int indexComposante);
    
    /**
     * Modifie la valeur de la première composante
     */
    void setValeur(double v);
    void setValeur(int index, double v);
    int getNbrComposantes();
};



#endif
