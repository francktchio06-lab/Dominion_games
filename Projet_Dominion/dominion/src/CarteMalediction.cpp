#include "CarteMalediction.h"
#include <iostream>

CarteMalediction::CarteMalediction()
    : Carte("Malédiction", 0, std::vector<TypeCarte>(1, TypeCarte::MALEDICTION),
            "-1 point") {
}

int CarteMalediction::pointsVictoire(const Joueur& /*j*/) const { return -1; }

void CarteMalediction::afficher() const {
    std::cout << getNom() << " (coût " << getCout() << ") : " << -1 << " point(s)" << std::endl;
}

