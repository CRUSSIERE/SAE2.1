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
    int getVitesseChoisie();

    private slots:
        void majVitesseChoisie(int valeur);

    private:
        Ui::Dialog * ui;
    int _vitesseChoisie;
};

#endif // DIALOG_H
