#include "Console.h"
#include <limits>
#include <iostream>
#include <cctype>


int Console::lireEntier(int min, int  max){

int n;
while(1){
  std::cout <<"#################### entrer un nombre compris entre "<<min<<" et "<<max<<std::endl;
  
  
  
  if(std::cin>>n){
  
       std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
  
      if(n<min || n>max) std::cout <<"############### veuillez recommencer monsieur############"<<std::endl;
    else{
    return n;
    }
    
  
  
  
  }else{

  if(std::cin.eof()){
    // fin de l'entrée : on garde l'état eof pour que les boucles de choix s'arrêtent
    return min;
  
  }
   else{ std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n') ;
  std::cout <<"############### veuillez recommencer monsieur############"<<std::endl;
  }

  }}
  return 0;

}


bool Console::lireOuiNon(std::string q) {
    std::string ligne;
    while (1) {
        std::cout << q << " (o/n) : ";
        if (!std::getline(std::cin, ligne)) {
            return false;
        }
        if (ligne.empty()) {
            std::cout << "Réponse vide, recommencez.\n";
            continue;
        }
        char c = static_cast<char>(std::tolower(static_cast<unsigned char>(ligne[0])));
        if (c == 'o') {
            return true;
        }
        if (c == 'n') {
            return false;
        }
        std::cout << "Répondez par o ou n.\n";
    }
}

void Console::titre( std::string t) {
    std::cout << "\n==== " << t << " ====\n";
}

void Console::effacer() {
    std::cout << "\033[2J\033[H";
}
// Couleur (code ANSI) d'un type de carte.
std::string Console::couleur(TypeCarte t) {
    switch (t) {
        case TypeCarte::TRESOR:      return "\033[33m";   // jaune
        case TypeCarte::VICTOIRE:    return "\033[32m";   // vert
        case TypeCarte::MALEDICTION: return "\033[35m";   // magenta
        case TypeCarte::ACTION:      return "\033[34m";   // bleu
        case TypeCarte::ATTAQUE:     return "\033[31m";   // rouge
        case TypeCarte::REACTION:    return "\033[36m";   // cyan
    }
    return "";
}

// Type utilisé pour choisir la couleur d'une carte (une carte peut en avoir plusieurs).
static TypeCarte typePrincipal(const Carte* c) {
    if (c->estAttaque())                  return TypeCarte::ATTAQUE;
    if (c->estReaction())                 return TypeCarte::REACTION;
    if (c->estAction())                   return TypeCarte::ACTION;
    if (c->estTresor())                   return TypeCarte::TRESOR;
    if (c->aType(TypeCarte::MALEDICTION)) return TypeCarte::MALEDICTION;
    return TypeCarte::VICTOIRE;
}

// Si numeroter est vrai, les cartes sont numérotées à partir de 1.
void Console::afficherPaquet(const Paquet& p, bool numeroter) {
    if (p.estVide()) {
        std::cout << "  (vide)\n";
        return;
    }
    for (int i = 0; i < p.taille(); ++i) {
        const Carte* c = p.voir(i);
        std::cout << "  ";
        if (numeroter) {
            std::cout << (i + 1) << ". ";
        }
        std::cout<<couleur(typePrincipal(c))  << c->getNom() << "\033[0m"
                  << " (coût " << c->getCout() << ") : " << c->getDescription() << "\n";
    }
}

void Console::afficherReserve(const Reserve& r) {
    titre("Réserve");
    r.afficher();
}

void Console::afficherJoueur(const Joueur& j) {
    titre(j.getNom());
    std::cout << "Actions : " << j.getActions()
              << "   Achats : " << j.getAchats()
              << "   Pièces : " << j.getPieces() << "\n";
    std::cout << "Pioche : " << j.getPioche().taille() << " carte(s)"
              << "   Défausse : " << j.getDefausse().taille() << " carte(s)\n";
    if (!j.getEnJeu().estVide()) {
        std::cout << "En jeu :\n";
        afficherPaquet(j.getEnJeu(), false);
    }
    std::cout << "Main :\n";
    afficherPaquet(j.getMain(), true);
}



