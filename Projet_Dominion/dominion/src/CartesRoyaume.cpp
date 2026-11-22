#include "CartesRoyaume.h"
#include "Joueur.h"
#include "Partie.h"
#include <algorithm>
#include <functional>
#include <iostream>

// ---------- Petits outils ----------

// Filtre qui accepte toutes les cartes.
static bool toutes(const Carte*) { return true; }

// Supprime de la main les cartes choisies : on part du plus GRAND indice
// pour que les indices suivants restent valides.
static void trierDecroissant(std::vector<int>& v) {
    std::sort(v.begin(), v.end(), std::greater<int>());
}

// Le joueur choisit une carte dans la Réserve (coût <= coutMax) et la reçoit en d.
static void gagnerCarte(Partie& p, Joueur& j, int coutMax, FiltreCarte f, Destination d) {
    std::string nom = j.choisirDansReserve(p.getReserve(), coutMax, f);
    if (!nom.empty() && p.donnerCarte(j, nom, d)) {
        std::cout << j.getNom() << " reçoit " << nom << "\n";
    }
}

// ================= Jardins =================
Jardins::Jardins() : CarteVictoire("Jardins", 4, 0) {
    m_description = "1 point par tranche de 10 cartes";
}

int Jardins::pointsVictoire(const Joueur& j) const {
    return j.nbCartesTotal() / 10;
}

// ================= CarteAttaque =================
CarteAttaque::CarteAttaque(const std::string& nom, int cout, const std::string& description,
                           int cartes, int actions, int achats, int pieces)
    : CarteAction(nom, cout, description, cartes, actions, achats, pieces,
                  {TypeCarte::ACTION, TypeCarte::ATTAQUE}) {
}

bool CarteAttaque::cibleProtegee(Joueur& cible) const {
    if (cible.getMain().compter("Douve") == 0) return false;
    if (cible.repondreOuiNon(cible.getNom() + ", révéler une Douve pour vous protéger ?")) {
        std::cout << cible.getNom() << " révèle une Douve et est protégé.\n";
        return true;
    }
    return false;
}

void CarteAttaque::effet(Partie& p, Joueur& j) const {
    std::vector<Joueur*> adv = p.adversaires(j);
    for (Joueur* cible : adv) {
        if (!cibleProtegee(*cible)) {
            attaquer(p, j, *cible);
        }
    }
}

// ================= Douve =================
Douve::Douve()
    : CarteAction("Douve", 2, "+2 cartes. Réaction : protège d'une attaque", 2, 0, 0, 0,
                  {TypeCarte::ACTION, TypeCarte::REACTION}) {
}

// ================= Cave =================
Cave::Cave()
    : CarteAction("Cave", 2, "+1 action. Défaussez des cartes, piochez autant", 0, 1, 0, 0) {
}

void Cave::effet(Partie&, Joueur& j) const {
    std::vector<int> idx = j.choisirCartesMain("Cartes à défausser", toutes, 0, j.getMain().taille());
    trierDecroissant(idx);
    for (int i : idx) j.defausserDepuisMain(i);
    std::cout << j.getNom() << " défausse et pioche " << idx.size() << " carte(s)\n";
    j.piocher(static_cast<int>(idx.size()));
}

// ================= Chapelle =================
Chapelle::Chapelle()
    : CarteAction("Chapelle", 2, "Écartez jusqu'à 4 cartes de votre main", 0, 0, 0, 0) {
}

void Chapelle::effet(Partie& p, Joueur& j) const {
    std::vector<int> idx = j.choisirCartesMain("Cartes à écarter (max 4)", toutes, 0, 4);
    trierDecroissant(idx);
    for (int i : idx) {
        const Carte* c = j.ecarterDepuisMain(i, p.getRebut());
        if (c) std::cout << j.getNom() << " écarte " << c->getNom() << "\n";
    }
}

// ================= Chancelier =================
Chancelier::Chancelier()
    : CarteAction("Chancelier", 3, "+2 pièces. Vous pouvez mettre votre pioche dans la défausse",
                  0, 0, 0, 2) {
}

void Chancelier::effet(Partie&, Joueur& j) const {
    if (j.repondreOuiNon("Mettre votre pioche dans votre défausse ?")) {
        j.getPioche().transfererTout(j.getDefausse());
        std::cout << j.getNom() << " met sa pioche dans sa défausse\n";
    }
}

// ================= Atelier =================
Atelier::Atelier()
    : CarteAction("Atelier", 3, "Recevez une carte coûtant jusqu'à 4", 0, 0, 0, 0) {
}

void Atelier::effet(Partie& p, Joueur& j) const {
    gagnerCarte(p, j, 4, toutes, Destination::DEFAUSSE);
}

// ================= Festin =================
Festin::Festin()
    : CarteAction("Festin", 4, "Écartez cette carte. Recevez une carte coûtant jusqu'à 5", 0, 0, 0, 0) {
}

void Festin::effet(Partie& p, Joueur& j) const {
    // Le Festin est « en jeu » : on le retire de là pour l'écarter.
    Paquet& enJeu = j.getEnJeu();
    for (int i = enJeu.taille() - 1; i >= 0; --i) {
        if (enJeu.voir(i) == this) {
            p.ecarter(enJeu.retirer(i));
            std::cout << j.getNom() << " écarte le Festin\n";
            break;
        }
    }
    gagnerCarte(p, j, 5, toutes, Destination::DEFAUSSE);
}

// ================= Prêteur sur gages =================
PreteurSurGages::PreteurSurGages()
    : CarteAction("Prêteur sur gages", 4, "Écartez un Cuivre de votre main : +3 pièces", 0, 0, 0, 0) {
}

void PreteurSurGages::effet(Partie& p, Joueur& j) const {
    int i = j.choisirCarteMain("Cuivre à écarter",
                               [](const Carte* c) { return c->getNom() == "Cuivre"; }, false);
    if (i < 0) return;
    j.ecarterDepuisMain(i, p.getRebut());
    j.ajouterPieces(3);
    std::cout << j.getNom() << " écarte un Cuivre : +3 pièces\n";
}

// ================= Rénovation =================
Renovation::Renovation()
    : CarteAction("Rénovation", 4, "Écartez une carte, recevez une carte coûtant jusqu'à 2 de plus",
                  0, 0, 0, 0) {
}

void Renovation::effet(Partie& p, Joueur& j) const {
    int i = j.choisirCarteMain("Carte à écarter", toutes, false);
    if (i < 0) return;
    const Carte* c = j.ecarterDepuisMain(i, p.getRebut());
    std::cout << j.getNom() << " écarte " << c->getNom() << "\n";
    gagnerCarte(p, j, c->getCout() + 2, toutes, Destination::DEFAUSSE);
}

// ================= Mine =================
Mine::Mine()
    : CarteAction("Mine", 5, "Écartez un Trésor, recevez en main un Trésor coûtant jusqu'à 3 de plus",
                  0, 0, 0, 0) {
}

void Mine::effet(Partie& p, Joueur& j) const {
    int i = j.choisirCarteMain("Trésor à écarter", [](const Carte* c) { return c->estTresor(); }, true);
    if (i < 0) return;
    const Carte* c = j.ecarterDepuisMain(i, p.getRebut());
    std::cout << j.getNom() << " écarte " << c->getNom() << "\n";
    gagnerCarte(p, j, c->getCout() + 3, [](const Carte* t) { return t->estTresor(); },
                Destination::MAIN);
}

// ================= Salle du trône =================
SalleDuTrone::SalleDuTrone()
    : CarteAction("Salle du trône", 4, "Jouez deux fois une carte Action de votre main", 0, 0, 0, 0) {
}

void SalleDuTrone::effet(Partie& p, Joueur& j) const {
    int i = j.choisirCarteMain("Action à jouer deux fois", [](const Carte* c) { return c->estAction(); },
                               true);
    if (i < 0) return;
    const Carte* c = j.jouerDepuisMain(i);
    const CarteAction* a = dynamic_cast<const CarteAction*>(c);
    if (a == nullptr) return;
    std::cout << j.getNom() << " joue deux fois " << a->getNom() << "\n";
    a->jouer(p, j);
    a->jouer(p, j);
}

// ================= Chambre du conseil =================
ChambreDuConseil::ChambreDuConseil()
    : CarteAction("Chambre du conseil", 5, "+4 cartes, +1 achat. Chaque autre joueur pioche 1 carte",
                  4, 0, 1, 0) {
}

void ChambreDuConseil::effet(Partie& p, Joueur& j) const {
    for (Joueur* autre : p.adversaires(j)) autre->piocher(1);
}

// ================= Bibliothèque =================
Bibliotheque::Bibliotheque()
    : CarteAction("Bibliothèque", 5, "Piochez jusqu'à 7 cartes (vous pouvez mettre de côté les Actions)",
                  0, 0, 0, 0) {
}

void Bibliotheque::effet(Partie&, Joueur& j) const {
    Paquet deCote;
    Paquet& main = j.getMain();
    while (main.taille() < 7) {
        int avant = main.taille();
        j.piocher(1);
        if (main.taille() == avant) break;              // plus rien à piocher
        const Carte* c = main.voir(main.taille() - 1);   // la carte piochée est à la fin
        if (c->estAction() && j.repondreOuiNon("Mettre de côté " + c->getNom() + " ?")) {
            deCote.ajouter(main.retirer(main.taille() - 1));
        }
    }
    deCote.transfererTout(j.getDefausse());
}

// ================= Aventurier =================
Aventurier::Aventurier()
    : CarteAction("Aventurier", 6, "Révélez des cartes jusqu'à 2 Trésors, prenez-les en main",
                  0, 0, 0, 0) {
}

void Aventurier::effet(Partie&, Joueur& j) const {
    Paquet revelees;
    int tresors = 0;
    while (tresors < 2) {
        const Carte* c = j.reveler();
        if (c == nullptr) break;
        if (c->estTresor()) {
            j.getMain().ajouter(c);
            ++tresors;
            std::cout << j.getNom() << " trouve " << c->getNom() << "\n";
        } else {
            revelees.ajouter(c);
        }
    }
    revelees.transfererTout(j.getDefausse());
}

// ================= Milice =================
Milice::Milice()
    : CarteAttaque("Milice", 4, "+2 pièces. Les autres joueurs défaussent jusqu'à 3 cartes",
                   0, 0, 0, 2) {
}

void Milice::attaquer(Partie&, Joueur&, Joueur& cible) const {
    int n = cible.getMain().taille() - 3;
    if (n <= 0) return;
    std::vector<int> idx = cible.choisirCartesMain(
        cible.getNom() + ", défaussez " + std::to_string(n) + " carte(s)", toutes, n, n);
    trierDecroissant(idx);
    for (int i : idx) cible.defausserDepuisMain(i);
    std::cout << cible.getNom() << " défausse " << idx.size() << " carte(s)\n";
}

// ================= Sorcière =================
Sorciere::Sorciere()
    : CarteAttaque("Sorcière", 5, "+2 cartes. Les autres joueurs reçoivent une Malédiction",
                   2, 0, 0, 0) {
}

void Sorciere::attaquer(Partie& p, Joueur&, Joueur& cible) const {
    if (p.donnerCarte(cible, "Malédiction", Destination::DEFAUSSE)) {
        std::cout << cible.getNom() << " reçoit une Malédiction\n";
    }
}

// ================= Bureaucrate =================
Bureaucrate::Bureaucrate()
    : CarteAttaque("Bureaucrate", 4,
                   "Recevez un Argent sur votre pioche. Les autres remettent une Victoire sur leur pioche",
                   0, 0, 0, 0) {
}

void Bureaucrate::effet(Partie& p, Joueur& j) const {
    if (p.donnerCarte(j, "Argent", Destination::PIOCHE)) {
        std::cout << j.getNom() << " met un Argent sur sa pioche\n";
    }
    CarteAttaque::effet(p, j);   // puis l'attaque normale
}

void Bureaucrate::attaquer(Partie&, Joueur&, Joueur& cible) const {
    int i = cible.choisirCarteMain(cible.getNom() + ", carte Victoire à remettre sur votre pioche",
                                   [](const Carte* c) { return c->estVictoire(); }, false);
    if (i < 0) {
        std::cout << cible.getNom() << " n'a pas de carte Victoire\n";
        return;
    }
    const Carte* c = cible.getMain().retirer(i);
    cible.recevoir(c, Destination::PIOCHE);
    std::cout << cible.getNom() << " remet " << c->getNom() << " sur sa pioche\n";
}

// ================= Espion =================
Espion::Espion()
    : CarteAttaque("Espion", 4,
                   "+1 carte, +1 action. Chaque joueur révèle sa 1re carte : défaussée ou remise",
                   1, 1, 0, 0) {
}

// Le décideur regarde la carte du dessus de la pioche de la cible et choisit.
static void espionner(Joueur& decideur, Joueur& cible) {
    const Carte* c = cible.reveler();
    if (c == nullptr) return;
    std::cout << cible.getNom() << " révèle " << c->getNom() << "\n";
    if (decideur.repondreOuiNon("Défausser " + c->getNom() + " de " + cible.getNom() + " ?")) {
        cible.getDefausse().ajouter(c);
    } else {
        cible.getPioche().ajouterDessus(c);
    }
}

void Espion::effet(Partie& p, Joueur& j) const {
    espionner(j, j);             // le joueur aussi (la Douve ne s'applique pas à lui)
    CarteAttaque::effet(p, j);
}

void Espion::attaquer(Partie&, Joueur& attaquant, Joueur& cible) const {
    espionner(attaquant, cible);
}

// ================= Voleur =================
Voleur::Voleur()
    : CarteAttaque("Voleur", 4,
                   "Les autres révèlent 2 cartes ; vous écartez un Trésor et pouvez le recevoir",
                   0, 0, 0, 0) {
}

void Voleur::attaquer(Partie& p, Joueur& attaquant, Joueur& cible) const {
    std::vector<const Carte*> tresors;
    for (int k = 0; k < 2; ++k) {
        const Carte* c = cible.reveler();
        if (c == nullptr) break;
        std::cout << cible.getNom() << " révèle " << c->getNom() << "\n";
        if (c->estTresor()) tresors.push_back(c);
        else cible.getDefausse().ajouter(c);
    }
    if (tresors.empty()) return;

    int choix = 0;
    if (tresors.size() > 1) choix = attaquant.choisirParmi("Trésor à écarter", tresors);
    if (choix < 0 || choix >= static_cast<int>(tresors.size())) choix = 0;
    const Carte* vole = tresors[choix];
    tresors.erase(tresors.begin() + choix);
    for (const Carte* t : tresors) cible.getDefausse().ajouter(t);   // l'autre est défaussé

    if (attaquant.repondreOuiNon("Recevoir " + vole->getNom() + " ?")) {
        attaquant.recevoir(vole, Destination::DEFAUSSE);
        std::cout << attaquant.getNom() << " vole " << vole->getNom() << "\n";
    } else {
        p.ecarter(vole);
        std::cout << vole->getNom() << " est écarté\n";
    }
}
