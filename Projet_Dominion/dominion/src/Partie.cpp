#include "Partie.h"
#include "Joueur.h"
#include "JoueurIA.h"
#include "JoueurHumain.h"
#include <algorithm>
#include <iostream>
#include "Console.h"
#include "CarteAction.h"

Partie::Partie(const ConfigPartie& config):
m_config(config),courant(0),numeroTour(0),m_rng(config.graine){

initialiser();
}


Partie::~Partie(){
  
  for(size_t i=0;i<joueurs.size();i++){
  
  
      delete(joueurs[i]);}


}


Reserve& Partie::getReserve(){ return reserve;}

Paquet& Partie:: getRebut(){ return rebut;}

const Catalogue& Partie:: getCatalogue() const { return catalogue;}

std::mt19937& Partie:: getRng() { return m_rng;}

void  Partie::ecarter(const Carte* c){  rebut.ajouter(c);}

bool Partie:: donnerCarte(Joueur& j, const std::string& nom, Destination d){

  const Carte* c= reserve.prendre(nom);
  if (c== nullptr) return false;
  j.recevoir(c,d);
  return true;
}

std::vector<Joueur*> Partie :: adversaires(const Joueur& j){

    std::vector<Joueur*> versus;
    
    for(size_t i=0;i<joueurs.size();i++){
      
        if(&j!=joueurs[i]) versus.push_back(joueurs[i]);
      
    
    }
    return versus;
    
    }
    
    
void Partie::distribuerDecksInitiaux(){


for(size_t i=0;i<joueurs.size();i++){

    for (size_t j=0;j<7;j++) joueurs[i]->recevoir(catalogue.get("Cuivre"));
    for(size_t j=0;j<3;j++) joueurs[i]->recevoir(catalogue.get("Domaine"));
    joueurs[i]->ajustement();
    

}


}



void Partie::creerJoueurs() {
    for (int i = 0; i < m_config.nbJoueurs; ++i) {
        std::string nom = (static_cast<size_t>(i) < m_config.noms.size())
                              ? m_config.noms[i]
                              : "IA " + std::to_string(i + 1);
       bool estIA = true;
        if (static_cast<size_t>(i) < m_config.estIA.size()) {
            estIA = m_config.estIA[i];
        }
        if (estIA) {
            joueurs.push_back(new JoueurIA(nom, m_rng, 1));
        } else {
            joueurs.push_back(new JoueurHumain(nom, m_rng));
        }
       
    }
    // Plus tard, quand JoueurHumain existera :
    // if (i < m_config.estIA.size() && !m_config.estIA[i]) -> new JoueurHumain(nom, m_rng)
}


void Partie::initialiser() {

    std::vector<std::string> royaumes = m_config.royaumes;

    if (royaumes.empty()) {
        // On tire 10 cartes Royaume au hasard parmi les 25.
        royaumes = catalogue.nomsRoyaume();
        std::shuffle(royaumes.begin(), royaumes.end(), m_rng);
        if (royaumes.size() > 10) royaumes.resize(10);
    }

    reserve.initialiser(
        catalogue,
        royaumes,
        m_config.nbJoueurs,
        m_config.modeRapide
    );

    creerJoueurs();
    distribuerDecksInitiaux();
}


bool Partie::estTerminee() const {

  return reserve.provincesEpuisees() ||(reserve.nbPilesVides()>=3);
}



void Partie::phaseAchat(Joueur& j) {
    if(j.estHumain()) Console::afficherJoueur(j);
    int  coins=j.jouerTresors();
     if(j.estHumain()) std::cout<<"vous  jouez vos trésors:"<<coins<<" pieces"<<std::endl;
    
    while (j.getAchats() > 0) {
        std::string nom = j.choisirAchat(reserve);
        if (nom.empty() || !reserve.estDisponible(nom)) {
            break;
        }
        int cout = reserve.getPile(nom).getModele()->getCout();
        if (!j.utiliserAchat(cout)) {
            break;
        }
        donnerCarte(j, nom, Destination::DEFAUSSE);
        std::cout << j.getNom() << " achète " << nom << "\n";
    }
}





void Partie::phaseAction(Joueur& j) {
    while (j.getActions() > 0 && j.getMain().contientType(TypeCarte::ACTION)) {
        if (j.estHumain()) {
            Console::afficherJoueur(j);
        }
        int i = j.choisirAction();
        if (i < 0) {
            break;
        }
        const Carte* c = j.getMain().voir(i);
        if (c == nullptr || !c->estAction()) {
            break;
        }
        j.utiliserAction();
        j.jouerDepuisMain(i);
        std::cout << j.getNom() << " joue " << c->getNom() << "\n";
        const CarteAction* a = dynamic_cast<const CarteAction*>(c);
        if (a != nullptr) {
            a->jouer(*this, j);
        }
    }
}

void Partie::phaseAjustement(Joueur& j) {
    j.ajustement();
}

void Partie::jouerTour(Joueur& j) {
    j.debutTour();
    phaseAction(j);
    phaseAchat(j);
    phaseAjustement(j);
}

void Partie::lancer() {
    const int LIMITE_TOURS = 200;   // sécurité pendant la mise au point
    if (joueurs.empty()) {
        return;
    }
    while (!estTerminee() && numeroTour < LIMITE_TOURS) {
        Joueur& j = *joueurs[courant];
        std::cout << "--- Tour " << numeroTour + 1 << " : " << j.getNom() << " ---\n";
        jouerTour(j);
        courant = (courant + 1) % static_cast<int>(joueurs.size());
        if (courant == 0) {
            ++numeroTour;
        }
    }
    annoncerVainqueur();
}

std::vector<std::pair<std::string, int> > Partie::classement() const {
    std::vector<std::pair<std::string, int> > res;
    for (size_t i = 0; i < joueurs.size(); ++i) {
        res.push_back(std::make_pair(joueurs[i]->getNom(), joueurs[i]->compterPoints()));
    }
    std::stable_sort(res.begin(), res.end(),
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second > b.second;
        });
    return res;
}

void Partie::annoncerVainqueur() const {
    std::vector<std::pair<std::string, int> > rang = classement();
    std::cout << "\n=== Classement final ===\n";
    for (size_t i = 0; i < rang.size(); ++i) {
        std::cout << i + 1 << ". " << rang[i].first << " : " << rang[i].second << " point(s)\n";
    }
    if (!rang.empty()) {
        int meilleur = rang[0].second;
        std::cout << "Vainqueur(s) :";
        for (size_t i = 0; i < rang.size(); ++i) {
            if (rang[i].second == meilleur) {
                std::cout << " " << rang[i].first;
            }
        }
        std::cout << "\n";
    }
}
