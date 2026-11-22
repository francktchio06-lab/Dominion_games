#include <algorithm>
#include "Carte.h"

Carte::Carte(const std::string& nom, int cout,
             const std::vector<TypeCarte>& types, const std::string& description)
    : m_nom(nom), m_cout(cout), m_types(types), m_description(description) {
}
Carte::Carte(const std::string& nom, int cout)
    : m_nom(nom), m_cout(cout) {
}

const std::string& Carte::getNom() const { return m_nom; }
int Carte::getCout() const { return m_cout; }
const std::string& Carte::getDescription() const { return m_description; }

bool Carte::aType(TypeCarte t) const {
    return std::find(m_types.begin(), m_types.end(), t) != m_types.end();
}

bool Carte::estTresor() const   { return aType(TypeCarte::TRESOR); }
bool Carte::estVictoire() const { return aType(TypeCarte::VICTOIRE); }
bool Carte::estAction() const   { return aType(TypeCarte::ACTION); }
bool Carte::estAttaque() const  { return aType(TypeCarte::ATTAQUE); }
bool Carte::estReaction() const { return aType(TypeCarte::REACTION); }

int Carte::pointsVictoire(const Joueur& /*j*/) const { return 0; }


