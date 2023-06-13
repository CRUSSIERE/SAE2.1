#ifndef DIAPORAMA_H
#define DIAPORAMA_H

#include <QDialog>

namespace Ui {
class Diaporama;
}

class Diaporama : public QDialog
{
    Q_OBJECT

public:
    explicit Diaporama(QWidget * parent = nullptr);
    ~Diaporama();
    int getDiaporamaChoisi(); // Retourne le diaporama choisi par l'utilisateur

private slots:
    void majDiaporamaChoisi(int valeur); // Met à jour le diaporama choisi en fonction de la valeur sélectionnée

private:
    Ui::Diaporama * ui; // Interface utilisateur de la boîte de dialogue
    int _diaporamaChoisi; // Diaporama choisi par l'utilisateur

};

#endif // DIAPORAMA_H
