#ifndef CARTETRESOR_H
#define CARTETRESOR_H

#include "Carte.h"

class CarteTresor : public Carte {
public:
    CarteTresor(const std::string& nom, int cout, int valeur);

    int getValeur() const;

    void afficher() const;

private:
    int m_valeur;
};

#endif
