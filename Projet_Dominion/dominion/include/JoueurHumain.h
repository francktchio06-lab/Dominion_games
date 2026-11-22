#ifndef JOUEURHUMAIN_H
#define JOUEURHUMAIN_H
#include "Joueur.h"

/*

classe utilisé  pour représenter un joueur humain il sera  utilisé  pour le multiJoueur 

ici on implémentera  juste les fonctions laissé abstraite dans la classe principale Joueur
*/
class  JoueurHumain :public Joueur{

public: 
  
  JoueurHumain(std::string nom, std::mt19937& rng);
  
    int choisirAction() override;
    
    std::string choisirAchat(const Reserve& r) override;
    
    int choisirCarteMain(std::string q, FiltreCarte f, bool facultatif) override;
    
    std::vector<int> choisirCartesMain(std::string q, FiltreCarte f, int min, int max) override;
    
    std::string choisirDansReserve(const Reserve& r, int coutMax, FiltreCarte f) override;
    
    int choisirParmi(std::string q, std::vector<const Carte*> cartes) override;
    
    bool repondreOuiNon(std::string q) override;
    
    bool estHumain() const override;
  


};
#endif
