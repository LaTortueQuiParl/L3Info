typedef struct Joueur
{
    char* pseudo;
    unsigned int nbCartes;
    int* cartesEnMain;
}Joueur;

void PoserCarte(Joueur* j);
void AjoutCarte(Joueur* j, int i);
