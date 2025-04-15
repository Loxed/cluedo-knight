#include "header.h"

#include "ressources.h"

///fonctions std utile, pas besoin d'empreinter toute une librairie pour 3 livres!
using std::cout;
using std::endl;
using std::string;

int main()
{
    ///Fonction aléatoire
    srand(time(NULL));

    ///Initialisation d'allegro
    init_alleg();

    ///Charger les ressources
    Ressources m_ressources;

    ///lancer menu principal
    menu_principal(m_ressources);

    ///fermer allegro & sauvegarder + detruire ressources
    exit_alleg();

    return 0;
}
END_OF_MAIN()
