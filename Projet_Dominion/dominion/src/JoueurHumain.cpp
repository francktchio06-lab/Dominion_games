#include "JoueurHumain.h"
#include "Console.h"
#include "Reserve.h"
#include <iostream>
#include <algorithm>
JoueurHumain::JoueurHumain(std::string nom, std::mt19937& rng):
  Joueur(nom,rng){
}

int JoueurHumain::choisirAction() {
    std::cout << "Quelle action jouer ? (0 = passer)" << std::endl;
    while (true) {
        int choix = Console::lireEntier(0, main.taille());
        if (choix == 0) {
            return -1;
        }
        if (main.voir(choix - 1)->estAction()) {
            return choix - 1;
        }
        std::cout << "Ce n'est pas une carte Action." << std::endl;
    }
}
  
  
  bool JoueurHumain:: estHumain() const{
  
    return true;}
    
  bool JoueurHumain::repondreOuiNon(std::string q){
   return Console::lireOuiNon(q);
  
  }
  
  std::string JoueurHumain::choisirAchat(const Reserve&  r){
    
      Console::afficherReserve(r);
      std::cout<< "vous  avez : "<<pieces<<" pieces"<<std::endl;
      std::vector<std::string> cartes = r.cartesAchetables(pieces);
      if(cartes.empty()) {
      
            Console::titre("vous ne  pouvez rien acheter");
            return "";}
        else{
        
          for(size_t i=0; i<cartes.size();i++){
            std::cout<< i+1<< "- "<<cartes[i]<<" : "<< r.getPile(cartes[i]).getModele()->getCout ()<<std::endl;
          
          }
         std::cout<<"0- Ne rien Acheter"<<std::endl; }
        int choix= Console::lireEntier(0, static_cast<int> (cartes.size()));
        if(choix==0) return "";
        else return cartes[choix-1];
      
    
        return "";
  
  
  }
  
// Choisit UNE carte de la main respectant le filtre f. Renvoie son indice, ou -1.
int JoueurHumain::choisirCarteMain(std::string q, FiltreCarte f, bool facultatif) {
    bool possible = false;
    for (int i = 0; i < main.taille(); ++i) {
        if (f(main.voir(i))) possible = true;
    }
    if (!possible) return -1;

    std::cout << q << std::endl;
    Console::afficherPaquet(main, true);
    if (facultatif) std::cout << "  0. Aucune" << std::endl;
    while (true) {
        int choix = Console::lireEntier(facultatif ? 0 : 1, main.taille());
        if (choix == 0 || std::cin.eof()) return -1;
        if (f(main.voir(choix - 1))) return choix - 1;
        std::cout << "Carte non autorisée." << std::endl;
    }
}

// Choisit entre min et max cartes de la main (indices différents).
std::vector<int> JoueurHumain::choisirCartesMain(std::string q, FiltreCarte f, int min, int max) {
    int possibles = 0;
    for (int i = 0; i < main.taille(); ++i) {
        if (f(main.voir(i))) ++possibles;
    }
    if (max > possibles) max = possibles;
    if (min > max) min = max;

    std::vector<int> choix;
    while (static_cast<int>(choix.size()) < max) {
        std::cout << q << " (" << choix.size() << " choisie(s), min " << min
                  << ", max " << max << ")" << std::endl;
        for (int i = 0; i < main.taille(); ++i) {
            bool dejaPris = std::find(choix.begin(), choix.end(), i) != choix.end();
            std::cout << "  " << i + 1 << ". " << main.voir(i)->getNom()
                      << (dejaPris ? "  [choisie]" : "") << std::endl;
        }
        bool peutArreter = static_cast<int>(choix.size()) >= min;
        if (peutArreter) std::cout << "  0. Terminer" << std::endl;

        int c = Console::lireEntier(peutArreter ? 0 : 1, main.taille());
        if (c == 0 || std::cin.eof()) break;
        if (!f(main.voir(c - 1))) {
            std::cout << "Carte non autorisée." << std::endl;
        } else if (std::find(choix.begin(), choix.end(), c - 1) != choix.end()) {
            std::cout << "Carte déjà choisie." << std::endl;
        } else {
            choix.push_back(c - 1);
        }
    }
    return choix;
}

// Choisit une carte de la Réserve de coût <= coutMax respectant f. "" si aucune.
std::string JoueurHumain::choisirDansReserve(const Reserve& r, int coutMax, FiltreCarte f) {
    std::vector<std::string> noms;
    for (const std::string& nom : r.cartesAchetables(coutMax)) {
        if (f(r.getPile(nom).getModele())) noms.push_back(nom);
    }
    if (noms.empty()) {
        std::cout << "Aucune carte disponible." << std::endl;
        return "";
    }
    std::cout << "Choisissez une carte coûtant jusqu'à " << coutMax << " :" << std::endl;
    for (size_t i = 0; i < noms.size(); ++i) {
        std::cout << "  " << i + 1 << ". " << noms[i] << " (coût "
                  << r.getPile(noms[i]).getModele()->getCout() << ")" << std::endl;
    }
    int c = Console::lireEntier(1, static_cast<int>(noms.size()));
    return noms[c - 1];
}

// Choisit une carte dans une liste. Renvoie son indice.
int JoueurHumain::choisirParmi(std::string q, std::vector<const Carte*> cartes) {
    if (cartes.empty()) return -1;
    std::cout << q << std::endl;
    for (size_t i = 0; i < cartes.size(); ++i) {
        std::cout << "  " << i + 1 << ". " << cartes[i]->getNom() << std::endl;
    }
    return Console::lireEntier(1, static_cast<int>(cartes.size())) - 1;
}
