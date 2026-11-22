#ifndef CARTEVICTOIRE_H
#define CARTEVICTOIRE_H

#include "Carte.h"

class CarteVictoire : public Carte {
public:
    CarteVictoire(const std::string& nom, int cout, int points);

    void afficher() const override;
    int pointsVictoire(const Joueur& j) const override;

private:
    int m_points;
};

#endif
