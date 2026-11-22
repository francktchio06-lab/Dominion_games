#include "CarteVictoire.h"
#include <iostream>
#include <string>

CarteVictoire::CarteVictoire(const std::string& nom, int cout, int points)
    : Carte(nom, cout, std::vector<TypeCarte>(1, TypeCarte::VICTOIRE),
            std::to_string(points) + " point(s)"), m_points(points) {}

void CarteVictoire::afficher() const {
    std::cout << getNom() << " (coût " << getCout() << ") : " << m_points << " point(s)" << std::endl;
}

int CarteVictoire::pointsVictoire(const Joueur& /*j*/) const {
    return m_points;
}
