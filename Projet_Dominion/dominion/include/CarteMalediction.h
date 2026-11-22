#ifndef CARTEMALEDICTION_H
#define CARTEMALEDICTION_H

#include "Carte.h"

class CarteMalediction : public Carte {
public:
    CarteMalediction();
     void afficher() const;
    int pointsVictoire(const Joueur& j) const override;
};
 

#endif
