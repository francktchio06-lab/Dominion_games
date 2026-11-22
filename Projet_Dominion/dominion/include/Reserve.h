#ifndef RESERVE_H
#define RESERVE_H

#include <map>
#include <ostream>
#include <string>
#include <vector>
#include "Pile.h"

class Catalogue;   // déclaration anticipée : l'include est dans Reserve.cpp

// Les piles de cartes achetables, indexées par nom de carte.
// Contenu (règles) : trésors 60 Cuivre / 40 Argent / 30 Or (moins les 7 Cuivre x nbJoueurs
// des decks initiaux) ; victoire 8 (2 joueurs) ou 12 (3-4) ; Malédiction 10 x (nbJoueurs-1) ;
// Royaume 10 par pile (Jardins : 8 à 2 joueurs, 12 à 3-4) ; mode rapide : toutes les piles à 1.
class Reserve {
public:
    Reserve() = default;

    void initialiser(const Catalogue& cat, const std::vector<std::string>& royaumes,
                     int nbJoueurs, bool rapide);

    const Carte* prendre(const std::string& nom);          // nullptr si indisponible
    bool contient(const std::string& nom) const;           // la pile existe
    bool estDisponible(const std::string& nom) const;      // la pile existe ET n'est pas vide
    Pile& getPile(const std::string& nom);

    std::vector<std::string> cartesAchetables(int coutMax) const;
    int  nbPilesVides() const;
    bool provincesEpuisees() const;

    void afficher() const;
    const Pile& getPile(const std::string& nom) const;

private:
    std::map<std::string, Pile> m_piles;
    std::vector<std::string> m_ordre;   // ordre d'affichage
};

#endif
