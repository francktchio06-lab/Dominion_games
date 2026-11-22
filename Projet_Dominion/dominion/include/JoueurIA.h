#ifndef JOUEURIA_H
#define JOUEURIA_H
#include "Joueur.h"

class JoueurIA :public Joueur{

  int m_niveau;
  
  public:
      JoueurIA(std::string nom,std::mt19937& rng,int niveau);
      
int choisirAction();

std::string choisirAchat(const Reserve& r);

int choisirCarteMain(std::string q, FiltreCarte f, bool facultatif);

std::vector<int> choisirCartesMain(std::string q, FiltreCarte f, int min, int max);

std::string choisirDansReserve(const Reserve& r, int coutMax, FiltreCarte f);

int choisirParmi(std::string q, std::vector<const Carte*> cartes);

bool repondreOuiNon(std::string q);

bool estHumain() const;

      





};
#endif

