#include "image.h"

Image::Image(unsigned int pRang, string pCategorie, string pTitre, string pChemin) {
    // Initialise les attributs de l'objet Image avec les valeurs passées en paramètres
    _rang = pRang;
    _categorie = pCategorie;
    _titre = pTitre;
    _chemin = pChemin;
}

unsigned int Image::getRang() {
    // Retourne le rang de l'image
    return _rang;
}

string Image::getCategorie() {
    // Retourne la catégorie de l'image
    return _categorie;
}

string Image::getTitre() {
    // Retourne le titre de l'image
    return _titre;
}

string Image::getChemin() {
    // Retourne le chemin de l'image
    return _chemin;
}

void Image::afficher() {
    // Affiche les informations de l'image dans la console
    cout << "image( rang:" << getRang() << ", titre:" << getTitre() << ", categorie:" <<
        getCategorie() << ", chemin:" << getChemin() << ")" << endl;
}
