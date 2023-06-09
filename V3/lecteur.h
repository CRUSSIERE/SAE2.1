#ifndef LECTEUR_H
#define LECTEUR_H

#include <QMainWindow>
#include "image.h"
#include <vector>
#include <QTimer>

typedef vector<Image*> Diaporama;   // Structure de données contenant les infos sur les images

QT_BEGIN_NAMESPACE
namespace Ui { class lecteur; }
QT_END_NAMESPACE

class lecteur : public QMainWindow
{
    Q_OBJECT

public:
    lecteur(QWidget *parent = nullptr);
    ~lecteur();

public slots:
    void precedent();
    void suivant();
    void demarrerModeAuto();
    void arreterModeAuto();
    void changerDiaporama(unsigned int pNumDiaporama);    // permet de choisir un diaporama, 0 si aucun diaporama souhaité
    void afficher();            // affiche les informations sur lecteur-diaporama et image courante
    unsigned int nbImages();    // affiche la taille de _diaporama
    Image* imageCourante();     // retourne le pointeur vers l'image courante
    unsigned int getNumDiaporamaCourant(); //retourne le numéro du diaporama courant
    void aPropos();
    void chargerDiaporama();    // charge dans _diaporama les images du _numDiaporamaCourant
    void viderDiaporama();      // vide _diaporama de tous ses objets image et les delete
    void arreterModeAutoSuivant();
    void arreterModeAutoPrecedent();

private:
    Ui::lecteur *ui;
    unsigned _numDiaporamaCourant;   // numéro du diaporama courant, par défaut 0
    Diaporama _diaporama;            // pointeurs vers les images du diaporama
    unsigned int _posImageCourante;  /* position, dans le diaporama,
                                        de l'image courante.
                                        Indéfini quand diaporama vide.
                                        Démarre à 0 quand diaporama non vide */
    QTimer* _timer;
    bool _modeAuto = false;



};
#endif // LECTEUR_H
