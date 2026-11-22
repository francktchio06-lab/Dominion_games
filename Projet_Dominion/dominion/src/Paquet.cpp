#include <algorithm>
#include "Paquet.h"

void Paquet::ajouter(const Carte* c) {
    m_cartes.push_back(c);
}

void Paquet::ajouterDessus(const Carte* c) {
    m_cartes.insert(m_cartes.begin(), c);
}

const Carte* Paquet::prendreDessus() {
    return retirer(0);
}

const Carte* Paquet::retirer(int i) {
    if (i < 0 || i >= taille()) {
        return nullptr;
    }
    const Carte* c = m_cartes[i];             // on sauvegarde AVANT d'effacer
    m_cartes.erase(m_cartes.begin() + i);
    return c;
}

const Carte* Paquet::voir(int i) const {
    if (i < 0 || i >= taille()) {
        return nullptr;
    }
    return m_cartes[i];
}

void Paquet::melanger(std::mt19937& rng) {
    std::shuffle(m_cartes.begin(), m_cartes.end(), rng);
}

void Paquet::transfererTout(Paquet& dest) {
    if (&dest == this) {
        return;
    }
    for (const Carte* c : m_cartes) {
        dest.ajouter(c);
    }
    m_cartes.clear();
}

int Paquet::taille() const { return static_cast<int>(m_cartes.size()); }

bool Paquet::estVide() const { return m_cartes.empty(); }

int Paquet::compter(const std::string& nom) const {
    int cpt = 0;
    for (const Carte* c : m_cartes) {
        if (c->getNom() == nom) {
            ++cpt;
        }
    }
    return cpt;
}

bool Paquet::contientType(TypeCarte t) const {
    for (const Carte* c : m_cartes) {
        if (c->aType(t)) {
            return true;
        }
    }
    return false;
}

std::vector<int> Paquet::indicesType(TypeCarte t) const {
    std::vector<int> res;
    for (int i = 0; i < taille(); ++i) {
        if (m_cartes[i]->aType(t)) {
            res.push_back(i);
        }
    }
    return res;
}

const std::vector<const Carte*>& Paquet::getCartes() const { return m_cartes; }

void Paquet::afficher(std::ostream& os) const {
    for (int i = 0; i < taille(); ++i) {
        os << "[" << i << "] ";
        m_cartes[i]->afficher();
        os << "\n";
    }
}
