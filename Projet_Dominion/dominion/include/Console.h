#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include "Joueur.h"
#include "Paquet.h"
#include "Reserve.h"
#include <limits>

class Console{

public :
  
static int lireEntier(int min, int max);
static bool lireOuiNon(std::string q);
static void titre(std::string q);
static void afficherJoueur(const Joueur& j);
static void afficherReserve(const Reserve& r);
static void afficherPaquet(const Paquet& p, bool numeroter);
static std::string couleur(TypeCarte t);
static void effacer();
    




};



#endif
