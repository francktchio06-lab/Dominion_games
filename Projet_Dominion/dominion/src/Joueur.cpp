#include "Joueur.h"
#include "CarteTresor.h"
#include <iostream>
Joueur::Joueur(std::string nom,std::mt19937& rng):

  m_nom(nom) ,actions(0),achats(0),pieces(0),
  m_rng(rng) {}
  
Joueur::~Joueur() {}

void  Joueur::debutTour(){

    actions = 1;
    achats = 1;
    pieces = 0;
}

//Compteurs : ajouterActions, ajouterAchats, ajouterPieces,
//utiliserAction, utiliserAchat	facile


void Joueur::ajouterActions(int n){

    actions+=n;

}

void Joueur::ajouterAchats(int n){

    achats+=n;
    }
    
void  Joueur::ajouterPieces(int n){

      pieces+=n;
      }
      
bool Joueur::utiliserAction(){
    if (actions<=0) return false;
    --actions;

    return true; // vérifie si il reste encore des acions au xjouers
    
    }
    
bool Joueur::utiliserAchat(int cout){
  
  if(achats<=0 || pieces<cout) return false;
  --achats;
  pieces-=cout;
  return true;

  }

std::string Joueur::getNom() const { return m_nom; }

Paquet& Joueur::getMain()     { return main; }
Paquet& Joueur::getPioche()   { return pioche; }
Paquet& Joueur::getDefausse() { return defausse; }
Paquet& Joueur::getEnJeu()    { return enJeu; }

int Joueur::getActions() const { return actions; }
int Joueur::getAchats() const  { return achats; }
int Joueur::getPieces() const  { return pieces; }




/// j'attend serge pour faire la suite nbre carte total et compter points
 int Joueur::nbCartesTotal() const {
      return pioche.taille() + main.taille() + enJeu.taille() + defausse.taille();
  }
  

/*  Appelée quand la pioche est vide.
Deux étapes : mélanger la défausse avec m_rng, puis la transférer dans la pioche.
Piège : mélanger avant de transférer, sinon tu mélanges une pioche vide.
    */
void Joueur::reformerPioche(){
  
  defausse.melanger(m_rng);
  defausse.transfererTout(pioche);
  }
  
  
  
  
    
 
  
  
  /*
  void piocher(n int)
  Répète n fois : si la pioche est vide, la reformer ; si elle est encore vide (défausse vide aussi), arrêter ; sinon prendre la carte du dessus et la mettre en main.
Piège : mets la carte à la fin de la main (ajouter, pas ajouterDessus). La Bibliothèque de ton binôme retrouve la carte qu’elle vient de piocher à cet endroit.*/

void Joueur::piocher(int n){

  for (int i=0;i<n;i++){
  
       if (pioche.estVide()) {
       
           reformerPioche();
       
          if(pioche.estVide()) return ;
          
          }
          
       main.ajouter(pioche.prendreDessus());
       
       }
 

}

 /*Les Paquet te donnent tout ce qu’il faut : ajouter (en dessous), ajouterDessus, prendreDessus, retirer(i), voir(i), melanger(rng), transfererTout(dest), taille(), estVide() et getCartes(). Les fonctions qui retirent renvoient nullptr si le paquet est vide ou si l’indice est invalide.*/

/*Envoie une carte dans la zone d : défausse, main, ou dessus de la pioche.
Un switch sur d. Comme Destination est un enum class, tu écris Destination::MAIN.
Piège : si c vaut nullptr (la Réserve n’avait plus la carte), ne fais rien.
Appelée par Partie::donnerCarte après un achat, et par les effets de cartes (Atelier, Festin…).
*/


void Joueur::recevoir(const Carte* c, Destination d ){

  if(c==nullptr) return ;  
  
  switch (d){
    
  case Destination::DEFAUSSE:
      defausse.ajouter(c);
      break;
  case Destination::PIOCHE:
      pioche.ajouterDessus(c);
      break;
  case Destination :: MAIN:
    main.ajouter(c);
    break;
    

  }


}

/*Elle prend la carte d’indice i dans la main, la place « en jeu » et la renvoie à l’appelant. La Partie s’en sert ensuite pour déclencher l’effet de la carte.*/
const Carte* Joueur::jouerDepuisMain(int i){


  const Carte* c= main.retirer(i);
  
  if(c!=nullptr) enJeu.ajouter(c);
  return c;


}

void  Joueur::defausserDepuisMain(int i){
    const Carte* c= main.retirer(i);
  
  if(c!=nullptr) defausse.ajouter(c);
  

}

const Carte* Joueur::ecarterDepuisMain(int i,Paquet& rebut){
    const Carte* c= main.retirer(i);
  
  if(c!=nullptr) rebut.ajouter(c);
  return c;

}


/*Elle joue tous les trésors de la main d’un coup : chaque trésor passe de la main à « en jeu », ses pièces s’additionnent, le total est ajouté à pieces et renvoyé (type int).

Les étapes
Un compteur total qui démarre à 0.
Un parcours de la main, de la dernière carte à la première (indice taille() - 1 jusqu’à 0).
Pour chaque indice, regarder la carte avec voir(i) (sans la retirer) et tester estTresor(). Si ce n’est pas un trésor, passer à la suivante.
Si c’est un trésor, lire sa valeur (voir plus bas), la retirer de la main avec retirer(i), la mettre dans enJeu, et ajouter la valeur à total.
Après la boucle, ajouter total aux pièces avec ta fonction ajouterPieces, puis renvoyer total.*/


int Joueur::jouerTresors() {
    int cpt = 0;



    for (int i = main.taille() - 1; i >= 0; --i) {
        const Carte* c = main.voir(i);


        if (c->estTresor()) {
            const CarteTresor* t = dynamic_cast<const CarteTresor*>(c);

            if (t != nullptr) {
                
                cpt += t->getValeur();
            } else {
                std::cout << "ERREUR : conversion vers CarteTresor impossible !\n";
            }

            enJeu.ajouter(main.retirer(i));
        }
    }

    ajouterPieces(cpt);

 
    return cpt;
}

const Carte* Joueur::reveler(){
  if (pioche.estVide()) reformerPioche();
  return pioche.prendreDessus();
}

void Joueur::ajustement(){
  
  int taille=5;
  main.transfererTout(defausse);
  enJeu.transfererTout(defausse);
  piocher(taille);
  


}
int Joueur::compterPoints() const {
    const Paquet* zones[] = { &pioche, &main, &enJeu, &defausse };
    int total = 0;
    for (const Paquet* z : zones) {
        for (const Carte* c : z->getCartes()) {
            total += c->pointsVictoire(*this);
        }
    }
    return total;
}

const Paquet& Joueur::getMain() const     { return main; }
const Paquet& Joueur::getPioche() const   { return pioche; }
const Paquet& Joueur::getDefausse() const { return defausse; }
const Paquet& Joueur::getEnJeu() const    { return enJeu; }
