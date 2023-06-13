#include "vitesse.h"
#include "ui_vitesse.h"
#include <iostream>

using namespace std;

Vitesse::Vitesse(QWidget * parent):
    QDialog(parent),
    ui(new Ui::Vitesse) {

    ui -> setupUi(this);

    // Connecte le signal valueChanged(int) de spinBox au slot majVitesseChoisie(int)
    connect(ui -> spinBox, SIGNAL(valueChanged(int)), this, SLOT(majVitesseChoisie(int)));

    // Définit les propriétés de spinBox
    ui -> spinBox -> setMinimum(1);         // Valeur minimale du spinBox
    ui -> spinBox -> setSingleStep(1);      // Incrément/decrement du spinBox lorsque l'on utilise les touches de flèche
    ui -> spinBox -> setValue(2);           // Valeur par défaut du spinBox
}

void Vitesse::majVitesseChoisie(int valeur) {
    // Met à jour la vitesse choisie en multipliant la valeur du spinBox par 1000 (pour obtenir des millisecondes)
    _vitesseChoisie = valeur * 1000;
}

int Vitesse::getVitesseChoisie() {
    // Retourne la vitesse choisie
    return _vitesseChoisie;
}

Vitesse::~Vitesse() {
    delete ui;
}
