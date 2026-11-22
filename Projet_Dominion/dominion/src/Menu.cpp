#include "Menu.h"
#include "Console.h"
#include <iostream>
#include <string>
#include <random>


ConfigPartie Menu::configurer(){
  
  ConfigPartie config;
  
  Console :: titre("Dominion");
  int  nbJoueurs=Console::lireEntier(2,4);
  config.nbJoueurs=nbJoueurs;
  std::cout<<"vous avez entrer "<<nbJoueurs<<" joueurs"<<std::endl;
  for(int i=0; i<nbJoueurs;i++){
        std::string nom;
        std::cout<<"Nom du Joueur "<<i+1<<std::endl;
        std::getline(std::cin,nom);
        if(nom.empty()) nom="Joueur"+(std::to_string(i+1));
       
        config.noms.push_back(nom);
        config.estIA.push_back(!Console::lireOuiNon("Ce joueur est -il humain"));
       
        
        
        
  
      }
      std::random_device rd;
       config.graine= rd();
       config.modeRapide=Console::lireOuiNon("voulez-vous jouez en mode rapide");
       return config;

}
