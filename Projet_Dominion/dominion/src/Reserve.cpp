#include "Reserve.h"
#include "Catalogue.h"
#include <iostream>

// Nombre d'exemplaires d'une pile au départ (règles : voir le commentaire de Reserve.h).
static int quantiteDepart(const std::string& nom, int nbJoueurs, bool rapide) {
    if (rapide)                return 1;
    if (nom == "Cuivre")       return 60 - 7 * nbJoueurs;   // 7 Cuivre par deck initial
    if (nom == "Argent")       return 40;
    if (nom == "Or")           return 30;
    if (nom == "Domaine" || nom == "Duché" || nom == "Province")
                               return (nbJoueurs == 2) ? 8 : 12;
    if (nom == "Malédiction")  return 10 * (nbJoueurs - 1);
    if (nom == "Jardins")      return (nbJoueurs == 2) ? 8 : 12;
    return 10;                                              // autres cartes Royaume
}

void Reserve::initialiser(const Catalogue& cat, const std::vector<std::string>& royaumes,
                          int nbJoueurs, bool rapide) {
    m_piles.clear();
    m_ordre.clear();

    std::vector<std::string> noms;
    noms.push_back("Cuivre");
    noms.push_back("Argent");
    noms.push_back("Or");
    noms.push_back("Domaine");
    noms.push_back("Duché");
    noms.push_back("Province");
    noms.push_back("Malédiction");
    noms.insert(noms.end(), royaumes.begin(), royaumes.end());

    for (const std::string& nom : noms) {
        const Carte* c = cat.get(nom);
        if (c == nullptr) {
            continue;   // carte pas (encore) dans le catalogue : on ignore
        }
        m_piles.insert(std::make_pair(nom, Pile(c, quantiteDepart(nom, nbJoueurs, rapide))));
        m_ordre.push_back(nom);
    }
}

const Carte* Reserve::prendre(const std::string& nom) {
    std::map<std::string, Pile>::iterator it = m_piles.find(nom);
    if (it == m_piles.end()) {
        return nullptr;
    }
    return it->second.prendre();   // nullptr si la pile est vide
}

bool Reserve::contient(const std::string& nom) const {
    return m_piles.find(nom) != m_piles.end();
}

bool Reserve::estDisponible(const std::string& nom) const {
    std::map<std::string, Pile>::const_iterator it = m_piles.find(nom);
    return it != m_piles.end() && !it->second.estVide();
}

// Le nom doit exister (sinon std::out_of_range) : tester contient() avant si besoin.
Pile& Reserve::getPile(const std::string& nom) {
    return m_piles.at(nom);
}

std::vector<std::string> Reserve::cartesAchetables(int coutMax) const {
    std::vector<std::string> res;
    for (const std::string& nom : m_ordre) {
        const Pile& p = m_piles.at(nom);
        if (!p.estVide() && p.getModele()->getCout() <= coutMax) {
            res.push_back(nom);
        }
    }
    return res;
}

int Reserve::nbPilesVides() const {
    int n = 0;
    for (std::map<std::string, Pile>::const_iterator it = m_piles.begin();
         it != m_piles.end(); ++it) {
        if (it->second.estVide()) {
            ++n;
        }
    }
    return n;
}

bool Reserve::provincesEpuisees() const {
    std::map<std::string, Pile>::const_iterator it = m_piles.find("Province");
    return it != m_piles.end() && it->second.estVide();
}

void Reserve::afficher() const {
    for (const std::string& nom : m_ordre) {
        const Pile& p = m_piles.at(nom);
        std::cout<< nom << " (coût " << p.getModele()->getCout() << ") : "
           << p.getQuantite() << " restante(s)\n";
    }
}
const Pile& Reserve::getPile(const std::string& nom) const {
    return m_piles.at(nom);
}
