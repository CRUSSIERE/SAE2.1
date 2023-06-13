#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
using namespace std;

class Image {
public:
    Image(unsigned int pRang = 0, string pCategorie = "", string pTitre = "", string pChemin = "");
    unsigned int getRang(); // Retourne le rang de l'image
    string getCategorie(); // Retourne la catégorie de l'image
    string getTitre(); // Retourne le titre de l'image
    string getChemin(); // Retourne le chemin de l'image
    void afficher(); // Affiche tous les champs de l'image

private:
    unsigned int _rang; // Rang de l'image dans le diaporama auquel elle est associée
    string _titre; // Intitulé de l'image
    string _categorie; // Catégorie de l'image (personne, animal, objet)
    string _chemin; // Chemin complet vers le dossier où se trouve l'image
};

#endif // IMAGE_H
