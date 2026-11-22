#ifndef PAQUET_H
#define PAQUET_H

#include <ostream>
#include <random>
#include <string>
#include <vector>
#include "Carte.h"

// Pile ordonnée de cartes : pioche, main, en jeu, défausse, rebut.
// NON propriétaire : ne stocke que des const Carte* (le Catalogue possède les cartes).
// Convention : l'indice 0 est le DESSUS du paquet.
//
// prendreDessus / retirer / voir renvoient nullptr si le paquet est vide
// ou si l'indice est invalide. Aucune exception.
class Paquet {
public:
    Paquet() = default;

    void ajouter(const Carte* c);                 // en dessous du paquet
    void ajouterDessus(const Carte* c);           // au-dessus du paquet
    const Carte* prendreDessus();                 // retire ET renvoie le dessus
    const Carte* retirer(int i);                  // retire ET renvoie la carte d'indice i
    const Carte* voir(int i) const;               // renvoie sans retirer

    void melanger(std::mt19937& rng);
    void transfererTout(Paquet& dest);            // vide ce paquet dans dest

    int  taille() const;
    bool estVide() const;
    int  compter(const std::string& nom) const;   // nb de cartes portant ce nom
    bool contientType(TypeCarte t) const;
    std::vector<int> indicesType(TypeCarte t) const;

    const std::vector<const Carte*>& getCartes() const;
    void afficher(std::ostream& os) const;

private:
    std::vector<const Carte*> m_cartes;
};

#endif
