
#ifndef TYPECARTE_H
#define TYPECARTE_H
#include <functional>

class Carte;
// définition des types possibles d'une carte

enum class TypeCarte {
  TRESOR,
  VICTOIRE,
  MALEDICTION,
  ACTION,
  ATTAQUE,
  REACTION
  
};




// Où une carte est envoyée (Joueur::recevoir, Partie::donnerCarte)
enum class Destination {
    DEFAUSSE,
    MAIN,
    PIOCHE
};

// Filtre sur les cartes, utilisé par les choix du joueur.
// Les cartes ne sont jamais copiées : on ne manipule que des const Carte*.
typedef std::function<bool(const Carte*)> FiltreCarte;
#endif
