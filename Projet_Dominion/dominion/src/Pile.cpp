#include "Pile.h"

Pile::Pile(const Carte* modele, int quantite)
    : m_modele(modele), m_quantite(quantite) {
}

const Carte* Pile::prendre() {
    if (m_quantite <= 0) {
        return nullptr;
    }
    --m_quantite;
    return m_modele;
}

void Pile::remettre() { ++m_quantite; }

const Carte* Pile::getModele() const { return m_modele; }
int Pile::getQuantite() const { return m_quantite; }
bool Pile::estVide() const { return m_quantite <= 0; }
