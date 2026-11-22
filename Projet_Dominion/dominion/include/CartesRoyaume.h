#ifndef CARTESROYAUME_H
#define CARTESROYAUME_H

#include "CarteAction.h"
#include "CarteVictoire.h"

// Les cartes Royaume qui ont un effet spécial.
// Les cartes « simples » (Village, Forgeron, Laboratoire, Bûcheron, Marché, Festival)
// sont de simples CarteAction créées directement dans le Catalogue.

// ---------- Carte Victoire spéciale ----------
class Jardins : public CarteVictoire {
public:
    Jardins();
    int pointsVictoire(const Joueur& j) const override;   // 1 point par tranche de 10 cartes
};

// ---------- Classe de base des attaques ----------
// effet() : pour chaque adversaire, s'il n'est pas protégé (Douve), on appelle attaquer().
class CarteAttaque : public CarteAction {
public:
    CarteAttaque(const std::string& nom, int cout, const std::string& description,
                 int cartes, int actions, int achats, int pieces);
protected:
    void effet(Partie& p, Joueur& j) const override;
    virtual void attaquer(Partie& p, Joueur& attaquant, Joueur& cible) const = 0;
private:
    bool cibleProtegee(Joueur& cible) const;
};

// ---------- Actions ----------
class Douve : public CarteAction {            // Réaction : +2 cartes (la protection est gérée par CarteAttaque)
public:
    Douve();
};

class Cave : public CarteAction {
public:
    Cave();
protected:
    void effet(Partie& p, Joueur& j) const override;
};

class Chapelle : public CarteAction {
public:
    Chapelle();
protected:
    void effet(Partie& p, Joueur& j) const override;
};

class Chancelier : public CarteAction {
public:
    Chancelier();
protected:
    void effet(Partie& p, Joueur& j) const override;
};

class Atelier : public CarteAction {
public:
    Atelier();
protected:
    void effet(Partie& p, Joueur& j) const override;
};

class Festin : public CarteAction {
public:
    Festin();
protected:
    void effet(Partie& p, Joueur& j) const override;
};

class PreteurSurGages : public CarteAction {
public:
    PreteurSurGages();
protected:
    void effet(Partie& p, Joueur& j) const override;
};

class Renovation : public CarteAction {
public:
    Renovation();
protected:
    void effet(Partie& p, Joueur& j) const override;
};

class SalleDuTrone : public CarteAction {
public:
    SalleDuTrone();
protected:
    void effet(Partie& p, Joueur& j) const override;
};

class ChambreDuConseil : public CarteAction {
public:
    ChambreDuConseil();
protected:
    void effet(Partie& p, Joueur& j) const override;
};

class Bibliotheque : public CarteAction {
public:
    Bibliotheque();
protected:
    void effet(Partie& p, Joueur& j) const override;
};

class Mine : public CarteAction {
public:
    Mine();
protected:
    void effet(Partie& p, Joueur& j) const override;
};

class Aventurier : public CarteAction {
public:
    Aventurier();
protected:
    void effet(Partie& p, Joueur& j) const override;
};

// ---------- Attaques ----------
class Milice : public CarteAttaque {
public:
    Milice();
protected:
    void attaquer(Partie& p, Joueur& attaquant, Joueur& cible) const override;
};

class Sorciere : public CarteAttaque {
public:
    Sorciere();
protected:
    void attaquer(Partie& p, Joueur& attaquant, Joueur& cible) const override;
};

class Bureaucrate : public CarteAttaque {
public:
    Bureaucrate();
protected:
    void effet(Partie& p, Joueur& j) const override;   // gagne un Argent, puis attaque
    void attaquer(Partie& p, Joueur& attaquant, Joueur& cible) const override;
};

class Espion : public CarteAttaque {
public:
    Espion();
protected:
    void effet(Partie& p, Joueur& j) const override;   // s'espionne lui-même, puis attaque
    void attaquer(Partie& p, Joueur& attaquant, Joueur& cible) const override;
};

class Voleur : public CarteAttaque {
public:
    Voleur();
protected:
    void attaquer(Partie& p, Joueur& attaquant, Joueur& cible) const override;
};

#endif
