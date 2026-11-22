#include "CarteAction.h"
#include "Joueur.h"
#include "Partie.h"
#include <iostream>

CarteAction::CarteAction(const std::string& nom, int cout, const std::string& description,
                         int cartes, int actions, int achats, int pieces,
                         const std::vector<TypeCarte>& types)
    : Carte(nom, cout, types, description),
      m_plusCartes(cartes), m_plusActions(actions), m_plusAchats(achats), m_plusPieces(pieces) {
}

void CarteAction::jouer(Partie& p, Joueur& j) const {
    j.piocher(m_plusCartes);
    j.ajouterActions(m_plusActions);
    j.ajouterAchats(m_plusAchats);
    j.ajouterPieces(m_plusPieces);
    effet(p, j);
}

void CarteAction::effet(Partie& /*p*/, Joueur& /*j*/) const {
}
void CarteAction:: afficher() const{
      
          std::cout << getNom() << " (coût " << getCout() << ") : " << m_plusCartes<< " de cartes en plus" <<m_plusActions<<" d'actions en plus"<<m_plusAchats<<" d'achat en plus" << m_plusPieces<<" de pieces  en plus"<<std::endl;

      }
