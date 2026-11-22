#include "JoueurIA.h"
#include "Reserve.h"
#include <vector>



JoueurIA::JoueurIA(std::string nom, std::mt19937& rng, int niveau):
Joueur(nom,rng), m_niveau(niveau){

}

bool JoueurIA::estHumain ()const{

  return false;

}


int JoueurIA::choisirAction() {
    std::vector<int> idx = main.indicesType(TypeCarte::ACTION);
    if (idx.empty()) {
        return -1;
    }
    return idx[0];
}

// Carte « inutile » : Malédiction ou Domaine (bonnes candidates pour écarter/défausser).
static bool inutile(const Carte* c) {
    return c->aType(TypeCarte::MALEDICTION) || c->getNom() == "Domaine";
}

std::string JoueurIA::choisirAchat(const Reserve& r) {
    if (pieces >= 8 && r.estDisponible("Province")) return "Province";
    if (pieces >= 6 && r.estDisponible("Or"))       return "Or";
    // Avec 4 ou 5 pièces : la carte Action la plus chère qu'elle peut payer.
    if (pieces >= 4) {
        std::string meilleur = choisirDansReserve(r, pieces,
                                                  [](const Carte* c) { return c->estAction(); });
        if (!meilleur.empty()) return meilleur;
    }
    if (pieces >= 3 && r.estDisponible("Argent"))   return "Argent";
    return "";
}

// La carte autorisée la moins chère (une Malédiction / un Cuivre en priorité).
int JoueurIA::choisirCarteMain(std::string /*q*/, FiltreCarte f, bool /*facultatif*/) {
    int meilleur = -1;
    for (int i = 0; i < main.taille(); ++i) {
        const Carte* c = main.voir(i);
        if (f(c) && (meilleur < 0 || c->getCout() < main.voir(meilleur)->getCout())) {
            meilleur = i;
        }
    }
    return meilleur;
}

// D'abord les cartes inutiles (jusqu'à max), puis on complète jusqu'à min.
std::vector<int> JoueurIA::choisirCartesMain(std::string /*q*/, FiltreCarte f, int min, int max) {
    std::vector<int> choix;
    for (int i = 0; i < main.taille() && static_cast<int>(choix.size()) < max; ++i) {
        if (f(main.voir(i)) && inutile(main.voir(i))) choix.push_back(i);
    }
    for (int i = 0; i < main.taille() && static_cast<int>(choix.size()) < min; ++i) {
        if (f(main.voir(i)) && !inutile(main.voir(i))) choix.push_back(i);
    }
    return choix;
}
std::string JoueurIA::choisirDansReserve(const Reserve& r, int coutMax, FiltreCarte f) {
    std::string meilleur = "";
    int coutMeilleur = -1;
    std::vector<std::string> noms = r.cartesAchetables(coutMax);
    for (const std::string& nom : noms) {
        const Carte* c = r.getPile(nom).getModele();
        if (f(c) && c->getCout() > coutMeilleur) {
            meilleur = nom;
            coutMeilleur = c->getCout();
        }
    }
    return meilleur;
}
// La carte la plus chère.
int JoueurIA::choisirParmi(std::string /*q*/, std::vector<const Carte*> cartes) {
    int meilleur = 0;
    for (size_t i = 1; i < cartes.size(); ++i) {
        if (cartes[i]->getCout() > cartes[meilleur]->getCout()) meilleur = static_cast<int>(i);
    }
    return meilleur;
}

// L'IA dit toujours oui (révéler la Douve, voler un trésor, Chancelier...).
bool JoueurIA::repondreOuiNon(std::string /*q*/) { return true; }
