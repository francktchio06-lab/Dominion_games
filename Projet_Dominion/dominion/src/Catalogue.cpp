#include "Catalogue.h"
#include "CarteTresor.h"
#include "CarteVictoire.h"
#include "CarteMalediction.h"
#include "CarteAction.h"
#include "CartesRoyaume.h"

// 7 cartes de base + 25 cartes Royaume.
Catalogue::Catalogue() {
    enregistrer(new CarteTresor("Cuivre", 0, 1));
    enregistrer(new CarteTresor("Argent", 3, 2));
    enregistrer(new CarteTresor("Or", 6, 3));
    enregistrer(new CarteVictoire("Domaine", 2, 1));
    enregistrer(new CarteVictoire("Duché", 5, 3));
    enregistrer(new CarteVictoire("Province", 8, 6));
    enregistrer(new CarteMalediction());
    enregistrer(new CarteAction("Village", 3, "+1 carte, +2 actions", 1, 2, 0, 0));
    enregistrer(new CarteAction("Laboratoire", 5, "+2 cartes, +1 action", 2, 1, 0, 0));
    enregistrer(new CarteAction("Bûcheron", 3, "+1 achat, +2 pièces", 0, 0, 1, 2));
    enregistrer(new CarteAction("Forgeron", 4, "+3 cartes", 3, 0, 0, 0));
    enregistrer(new CarteAction("Marché", 5, "+1 carte, +1 action, +1 achat, +1 pièce", 1, 1, 1, 1));
    enregistrer(new CarteAction("Festival", 5, "+2 actions, +1 achat, +2 pièces", 0, 2, 1, 2));
    // Cartes à effet spécial (CartesRoyaume.h)
    enregistrer(new Jardins());
    enregistrer(new Douve());
    enregistrer(new Cave());
    enregistrer(new Chapelle());
    enregistrer(new Chancelier());
    enregistrer(new Atelier());
    enregistrer(new Festin());
    enregistrer(new PreteurSurGages());
    enregistrer(new Renovation());
    enregistrer(new SalleDuTrone());
    enregistrer(new ChambreDuConseil());
    enregistrer(new Bibliotheque());
    enregistrer(new Mine());
    enregistrer(new Aventurier());
    enregistrer(new Milice());
    enregistrer(new Sorciere());
    enregistrer(new Bureaucrate());
    enregistrer(new Espion());
    enregistrer(new Voleur());
}

Catalogue::~Catalogue() {
    for (std::map<std::string, Carte*>::iterator it = m_cartes.begin();
         it != m_cartes.end(); ++it) {
        delete it->second;
    }
}

const Carte* Catalogue::get(const std::string& nom) const {
    std::map<std::string, Carte*>::const_iterator it = m_cartes.find(nom);
    if (it == m_cartes.end()) {
        return nullptr;
    }
    return it->second;
}

// Les cartes Royaume = toutes les cartes Action + Jardins.
std::vector<std::string> Catalogue::nomsRoyaume() const {
    std::vector<std::string> noms;
    for (std::map<std::string, Carte*>::const_iterator it = m_cartes.begin();
         it != m_cartes.end(); ++it) {
        if (it->second->estAction() || it->first == "Jardins") {
            noms.push_back(it->first);
        }
    }
    return noms;
}

void Catalogue::enregistrer(Carte* c) {
    m_cartes[c->getNom()] = c;
}
