#ifndef VITESSE_H
#define VITESSE_H

#include <QDialog>

namespace Ui {
    class Vitesse;
}

class Vitesse: public QDialog {
    Q_OBJECT

public:
    explicit Vitesse(QWidget * parent = nullptr);
    ~Vitesse();
    int getVitesseChoisie(); // Retourne la vitesse choisie par l'utilisateur

private slots:
    void majVitesseChoisie(int valeur); // Met à jour la vitesse choisie en fonction de la valeur sélectionnée

private:
    Ui::Vitesse * ui; // Interface utilisateur de la boîte de Vitesseue
    int _vitesseChoisie; // Vitesse choisie par l'utilisateur

};

#endif // VITESSE_H
