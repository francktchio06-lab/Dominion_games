#ifndef CONFIGPARTIE_H
#define CONFIGPARTIE_H

#include <string>
#include <vector>

enum class ModeRoyaume {
    IMPOSE,
    ALEATOIRE,
    MANUEL
};

struct ConfigPartie {
    int nbJoueurs = 2;
    std::vector<std::string> noms;
    std::vector<bool> estIA;
    bool modeRapide = false;
    ModeRoyaume modeRoyaume = ModeRoyaume::IMPOSE;
    std::vector<std::string> royaumes;
    unsigned graine = 0;
};

#endif
