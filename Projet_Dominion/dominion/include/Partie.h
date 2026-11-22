#ifndef PARTIE_H
#define PARTIE_H
// les include
#include "ConfigPartie.h"
#include "Catalogue.h"
#include "Reserve.h"
#include "TypeCarte.h"
#include "Paquet.h"
#include <vector>
#include <string>
#include <random> 
#include <utility>

class Joueur;
class Partie{

protected:
    ConfigPartie  m_config;
    Catalogue catalogue;
    Reserve reserve;
    Paquet rebut;
    std::vector<Joueur*>joueurs;
    int courant;
    int numeroTour;
    std::mt19937 m_rng;
public: 
  Partie(const ConfigPartie&  config);
  ~Partie();
  void lancer();
  void initialiser();
  void creerJoueurs();
  void distribuerDecksInitiaux();
  void jouerTour(Joueur& j);
  void phaseAction(Joueur& j);
  void phaseAjustement(Joueur& j);
  void phaseAchat(Joueur& j);
  bool estTerminee() const;
  std::vector<std::pair<std::string,int >> classement() const ;
  void annoncerVainqueur() const;
  
  // services offertes  aux cartes
  
  
  std::vector<Joueur*> adversaires(const Joueur& j);
  bool donnerCarte(Joueur& j, const std::string& nom, Destination d);
  void ecarter(const Carte* c);
  Reserve& getReserve(); 
  Paquet& getRebut();
  const Catalogue& getCatalogue() const;
  std::mt19937& getRng();
  
  
  
  
    


};

#endif
