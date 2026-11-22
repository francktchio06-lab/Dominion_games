#include "Partie.h"
#include "Menu.h"

int main() {
    ConfigPartie config= Menu::configurer();


    Partie partie(config);
    partie.lancer();
    return 0;
}
