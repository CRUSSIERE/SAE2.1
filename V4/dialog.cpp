#include "dialog.h"

#include "ui_dialog.h"

#include <iostream>

using namespace std;
Dialog::Dialog(QWidget * parent):
    QDialog(parent),
    ui(new Ui::Dialog) {

        ui -> setupUi(this);
        connect(ui -> spinBox, SIGNAL(valueChanged(int)), this, SLOT(majVitesseChoisie(int)));
        ui -> spinBox -> setMinimum(1);
        ui -> spinBox -> setSingleStep(1); // Will increment the current value with 1 (if you use up arrow key) (if you use down arrow key => -1)
        ui -> spinBox -> setValue(2); // Default/begining value
    }

void Dialog::majVitesseChoisie(int valeur) {
    _vitesseChoisie = valeur * 1000;

}

int Dialog::getVitesseChoisie() {
    return _vitesseChoisie;
}

Dialog::~Dialog() {
    delete ui;
}
