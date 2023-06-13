#include "diaporama.h"
#include "ui_diaporama.h"
#include <iostream>

using namespace std;

Diaporama::Diaporama(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Diaporama)
{
    ui -> setupUi(this);

    // Connecte le signal valueChanged(int) de spinBox au slot majDiaporamaChoisi(int)
    connect(ui -> spinBoxDiaporama, SIGNAL(valueChanged(int)), this, SLOT(majDiaporamaChoisi(int)));

    // Définit les propriétés de spinBox
    ui -> spinBoxDiaporama -> setMinimum(1);         // Valeur minimale du spinBox
    ui -> spinBoxDiaporama -> setMaximum(4);         // Valeur maximale du spinBox
    ui -> spinBoxDiaporama -> setSingleStep(1);      // Valeur d'incrémentation/décrémentation du spinBox lorsque l'on utilise les touches de flèches
    ui -> spinBoxDiaporama -> setValue(1);           // Valeur par défaut du spinBox
}

void Diaporama::majDiaporamaChoisi(int valeur) {
    // Met à jour le diaporama choisi
    _diaporamaChoisi = valeur;
}

int Diaporama::getDiaporamaChoisi() {
    // Retourne le diaporama choisi
    return _diaporamaChoisi;
}

Diaporama::~Diaporama() {
    delete ui;
}
