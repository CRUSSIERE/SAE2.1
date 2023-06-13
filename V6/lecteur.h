#ifndef LECTEUR_H
#define LECTEUR_H

#include <QMainWindow>
#include "database.h"
#include "image.h"
#include <vector>
#include <QTimer>

typedef vector <Image*> Diapo; // Structure de données contenant les infos sur les images

QT_BEGIN_NAMESPACE
namespace Ui {
    class lecteur;
}
QT_END_NAMESPACE

class lecteur : public QMainWindow {
    Q_OBJECT

public:
    lecteur(QWidget *parent = nullptr); // Constructeur de la classe
    ~lecteur(); // Destructeur de la classe

public slots:
    void precedent(); // Slot pour passer à l'image précédente dans le diaporama
    void suivant(); // Slot pour passer à l'image suivante dans le diaporama
    void demarrerModeAuto(); // Slot pour démarrer le mode de lecture automatique du diaporama
    void arreterModeAuto(); // Slot pour arrêter le mode de lecture automatique du diaporama
    void changerDiaporama(unsigned int pNumDiaporama); // Slot pour changer de diaporama
    void afficher(); // Slot pour afficher les informations sur le lecteur-diaporama et l'image courante
    unsigned int nbImages(); // Retourne le nombre d'images dans le diaporama
    Image* imageCourante(); // Retourne un pointeur vers l'image courante
    unsigned int getNumDiaporamaCourant(); // Retourne le numéro du diaporama courant
    void aPropos(); // Slot pour afficher des informations sur l'application
    void chargerDiaporama(); // Charge les images du diaporama depuis la base de données
    void viderDiaporama(); // Vide le diaporama de toutes ses images
    void arreterModeAutoSuivant(); // Slot pour arrêter le mode de lecture automatique après l'image suivante
    void arreterModeAutoPrecedent(); // Slot pour arrêter le mode de lecture automatique après l'image précédente
    void changerVitesse(); // Slot pour changer la vitesse de lecture du diaporama

private:
    Ui::lecteur* ui; // Interface utilisateur du lecteur-diaporama
    unsigned _numDiaporamaCourant = 0; // Numéro du diaporama courant, par défaut 0
    Diapo _diaporama; // Pointeurs vers les images du diaporama
    unsigned int _posImageCourante; // Position de l'image courante dans le diaporama
    QTimer* _timer; // Timer pour le mode de lecture automatique
    bool _modeAuto = false; // Indicateur du mode de lecture automatique, désactivé par défaut
    Database* _bddSAE; // Base de données

};

#endif // LECTEUR_H
