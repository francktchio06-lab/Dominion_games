#ifndef CARTEACTION_H
#define CARTEACTION_H

#include <string>
#include "Carte.h"

class Partie;   // déclarations anticipées : les includes sont dans CarteAction.cpp
class Joueur;

// Carte Action. Patron « méthode template » :
//   jouer(p, j) :  j.piocher(plusCartes);      j.ajouterActions(plusActions);
//                  j.ajouterAchats(plusAchats); j.ajouterPieces(plusPieces);
//                  effet(p, j);   // virtuelle : effet spécifique de la carte
class CarteAction : public Carte {
public:
    CarteAction(const std::string& nom, int cout, const std::string& description,
                int cartes, int actions, int achats, int pieces,
                const std::vector<TypeCarte>& types = std::vector<TypeCarte>(1, TypeCarte::ACTION));

    void jouer(Partie& p, Joueur& j) const;
    void afficher() const ;
protected:
    // Ne fait rien par défaut. Redéfinie par les cartes à effet spécial.
    virtual void effet(Partie& p, Joueur& j) const;

    int m_plusCartes;
    int m_plusActions;
    int m_plusAchats;
    int m_plusPieces;
};

#endif
