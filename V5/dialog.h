#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
    class Dialog;
}

class Dialog: public QDialog {
    Q_OBJECT

public:
    explicit Dialog(QWidget * parent = nullptr);
    ~Dialog();
    int getVitesseChoisie(); // Retourne la vitesse choisie par l'utilisateur

private slots:
    void majVitesseChoisie(int valeur); // Met à jour la vitesse choisie en fonction de la valeur sélectionnée

private:
    Ui::Dialog * ui; // Interface utilisateur de la boîte de dialogue
    int _vitesseChoisie; // Vitesse choisie par l'utilisateur

};

#endif // DIALOG_H
