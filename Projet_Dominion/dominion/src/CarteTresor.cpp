#include "CarteTresor.h"
#include <iostream>


CarteTresor::CarteTresor(const std::string& nom, int cout, int valeur)
    : Carte(nom, cout, {TypeCarte::TRESOR}, ""),
      m_valeur(valeur) {}

int CarteTresor::getValeur() const {
    return m_valeur;
}

void CarteTresor::afficher() const {
    std::cout << getNom() << " (coût " << getCout() << ") : +" << m_valeur << " pièce(s)" << std::endl;
}
