//
//  Classe.h
//  RecForme
//
//  Created by Hubert Godfroy on 11/06/12.
//  Copyright (c) 2012 Mines de Nancy. All rights reserved.
//

#ifndef RecForme_Classe_h
#define RecForme_Classe_h

class Classe {
    
    
public:
    Classe();
    ~Classe();
    virtual std::string toString();
    virtual bool equals(Classe* t) = 0;
};

#endif
