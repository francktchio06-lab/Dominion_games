#ifndef CARTE_H
#define CARTE_H

#include <ostream>
#include <string>
#include <vector>
#include "TypeCarte.h"

class Joueur;   // déclaration anticipée : pas d'include de Joueur.h ici

// Classe de base abstraite de toutes les cartes.
// Une carte est créée une seule fois par le Catalogue (qui la possède).
// Paquet, Pile et Reserve ne stockent que des const Carte*.
class Carte {
public:
    virtual ~Carte() = default;

    const std::string& getNom() const;
    int getCout() const;
    const std::string& getDescription() const;

    bool aType(TypeCarte t) const;
    bool estTresor() const;
    bool estVictoire() const;
    bool estAction() const;
    bool estAttaque() const;
    bool estReaction() const;

    // Points apportés au joueur j en fin de partie (0 par défaut).
    virtual int pointsVictoire(const Joueur& j) const;

    virtual void afficher() const =0;

protected:
    // Constructeur protégé : Carte est abstraite, seules les sous-classes l'appellent.
    Carte(const std::string& nom, int cout,
          const std::vector<TypeCarte>& types, const std::string& description);
    Carte(const std::string& nom, int cout);

    std::string m_nom;
    int m_cout;
    std::vector<TypeCarte> m_types;
    std::string m_description;
};

#endif
