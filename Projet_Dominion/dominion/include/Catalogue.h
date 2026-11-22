#ifndef CATALOGUE_H
#define CATALOGUE_H

#include <map>
#include <string>
#include <vector>
#include "Carte.h"

// Crée UN seul objet par type de carte (33) et les détruit dans ~Catalogue().
// Il est le seul PROPRIÉTAIRE des cartes ; tout le reste utilise des const Carte*.
// Non copiable (sinon double destruction des cartes).
class Catalogue {
public:
    Catalogue();
    ~Catalogue();
    Catalogue(const Catalogue&) = delete;
    Catalogue& operator=(const Catalogue&) = delete;

    const Carte* get(const std::string& nom) const;   // nullptr si le nom est inconnu
    std::vector<std::string> nomsRoyaume() const;     // noms des 25 cartes Royaume

private:
    void enregistrer(Carte* c);

    std::map<std::string, Carte*> m_cartes;
};

#endif
