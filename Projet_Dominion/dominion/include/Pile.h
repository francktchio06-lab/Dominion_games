#ifndef PILE_H
#define PILE_H

#include "Carte.h"

// Une pile de la Réserve : N exemplaires d'une même carte.
// Ne stocke qu'un pointeur vers la carte modèle (pas de copie).
class Pile {
public:
    Pile(const Carte* modele, int quantite);

    const Carte* prendre();        // quantité-1 et renvoie le modèle ; nullptr si vide
    void remettre();               // quantité+1

    const Carte* getModele() const;
    int  getQuantite() const;
    bool estVide() const;

private:
    const Carte* m_modele;
    int m_quantite;
};

#endif
