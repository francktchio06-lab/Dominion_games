#ifndef JOUEUR_H
#define JOUEUR_H

//les  includes
#include <string>
#include <random>
#include "Paquet.h"
#include "TypeCarte.h"
#include <vector>
class  Reserve;  // déclaration anticipée : l'include est dans Joueur.cpp
 


// Classe abstraite : un joueur (humain ou IA).
// Les décisions (choisir...) sont virtuelles pures : JoueurHumain et JoueurIA les définissent.
// Les effets des cartes (CarteAction) appellent cette interface : ses signatures publiques
// sont un CONTRAT avec le binôme, à ne pas changer sans le prévenir.

class Joueur{
  //les attributs  ils sont directements  en privés
protected:
  std::string m_nom;
  Paquet pioche;
  Paquet main;
  Paquet enJeu;
  Paquet deCote;
  Paquet defausse;
  int actions;
  int achats;
  int  pieces;
  std::mt19937& m_rng;
  
  
  public:
      // les constructeurs et les destructeurs
      Joueur(std::string nom,std::mt19937& rng);
      
     virtual  ~Joueur();
      
      // Deroulement  du tour 
      
      void debutTour();
      
      void piocher(int n);
      
      const Carte*  jouerDepuisMain(int i);
      
      int  jouerTresors();
      
      void defausserDepuisMain(int i);
      
      const Carte* ecarterDepuisMain(int i, Paquet& rebut);
      
      void recevoir(const Carte* c,Destination d = Destination::DEFAUSSE);
      
      void ajustement();
      
      void reformerPioche();
      
      // Retire et renvoie la carte du dessus de la pioche (reforme la pioche si besoin).
      // nullptr si pioche ET défausse sont vides.
      const Carte* reveler();
      
      //compteurs
      
      void ajouterActions(int n);
      
      void ajouterAchats(int n);
      
      void ajouterPieces(int n);
      
      bool utiliserAchat(int cout);
      
      bool utiliserAction();
      
      // les accesseurs
      
       std::string getNom() const;
      
      Paquet& getMain();
      
      Paquet& getPioche();
      
      Paquet& getDefausse();
      
      Paquet& getEnJeu();
      
       int getActions() const ;
      
       int  getAchats() const ;
      
       int getPieces() const ;
      
       int nbCartesTotal() const ;
      
       int compterPoints() const ;
       
 const Paquet& getMain() const;
const Paquet& getPioche() const;
const Paquet& getDefausse() const;
const Paquet& getEnJeu() const;
      
      // les décissions  où on va les affecter aux classes filles
      
      
      virtual int choisirAction()=0;
      
     virtual  std::string choisirAchat(const Reserve& r)=0;
      
     virtual int choisirCarteMain(std::string q,FiltreCarte f,bool facultatif)=0;
      
      virtual std::vector<int> choisirCartesMain(std::string ,FiltreCarte f,int min ,int max)=0;
      
      virtual std::string choisirDansReserve(const Reserve& r,int coutMax,FiltreCarte f)=0;
      
      virtual int choisirParmi(std::string q,std::vector<const Carte*>)=0;
      
     virtual bool repondreOuiNon(std::string q)=0;
      
      virtual bool estHumain() const =0;
      
      
      
      
  



};
#endif 
