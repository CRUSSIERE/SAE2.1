#include "lecteur.h"

Lecteur::Lecteur()
{
    _numDiaporamaCourant = 0;   // =  le lecteur est vide
}

void Lecteur::avancer()
{
    if (numDiaporamaCourant() > 0 && _posImageCourante < nbImages() - 1)
        {
            _posImageCourante++;
            cout << "Image suivante" << endl;
            imageCourante()->afficher();
        }
        else
        {
            cout << "Impossible d'avancer : fin du diaporama atteinte" << endl;
        }
}

void Lecteur::reculer()
{
    if (_posImageCourante > 0)
        {
            _posImageCourante--;
        }
        else
        {
            _posImageCourante = nbImages() - 1; // retourne à la fin du diaporama
        }
        cout << "Image " << _posImageCourante << " affichee." << endl;
}

void Lecteur::changerDiaporama(unsigned int pNumDiaporama)
{
    // s'il y a un diaporama courant, le vider, puis charger le nouveau Diaporama
    if (numDiaporamaCourant() > 0)
    {
        viderDiaporama();
    }
    _numDiaporamaCourant = pNumDiaporama;
    if (numDiaporamaCourant() > 0)
    {
        chargerDiaporama(); // charge le diaporama courant
    }

}

void Lecteur::chargerDiaporama()
{
    /* Chargement des images associées au diaporama courant
       Dans une version ultérieure, ces données proviendront d'une base de données,
       et correspondront au diaporama choisi */
    Image* imageACharger;
    imageACharger = new Image(3, "personne", "Blanche Neige", "C:\\cartesDisney\\carteDisney2.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(2, "personne", "Cendrillon", "C:\\cartesDisney\\carteDisney4.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(4, "animal", "Mickey", "C:\\cartesDisney\\carteDisney1.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(1, "personne", "Grincheux", "C:\\cartesDisney\\carteDisney1.gif");
    _diaporama.push_back(imageACharger);


     // trier le contenu du diaporama par ordre croissant selon le rang de l'image dans le diaporama
	 // A FAIRE

	 
     _posImageCourante = 0;

     cout << "Diaporama num. " << numDiaporamaCourant() << " selectionne. " << endl;
     cout << nbImages() << " images chargees dans le diaporama" << endl;

}

void Lecteur::viderDiaporama()
{
    if (nbImages () > 0)
    {
        unsigned int taille = nbImages();
        for (unsigned int i = 0; i < taille ; i++)
        {
            _diaporama.pop_back(); /* Removes the last element in the vector,
                                      effectively reducing the container size by one.
                                      AND deletes the removed element */
        }
     _posImageCourante = 0;
    }
    cout << nbImages() << " images restantes dans le diaporama." << endl;

}

void Lecteur::afficher()
{
    // afficher si le lecteur est vide ou afficher le numéro du diaporama courant
        if (numDiaporamaCourant() == 0)
        {
            cout << "Lecteur vide." << endl;
        }
        else
        {
            cout << "Diaporama numéro " << numDiaporamaCourant() << " est en cours de lecture." << endl;

            // afficher l'image courante si elle existe, sinon afficher "diaporama vide"
            if (nbImages() > 0)
            {
                Image* imageCourante = _diaporama[_posImageCourante];
                cout << "Image courante : " << imageCourante->getTitre() << endl;
            }
            else
            {
                cout << "Diaporama vide." << endl;
            }
        }
}

unsigned int Lecteur::nbImages()
{
    return _diaporama.size();
}

Image *Lecteur::imageCourante()
{
    return nullptr;
}

unsigned int Lecteur::numDiaporamaCourant()
{
    return 0;
}
