#include "lecteur.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    lecteur w;
    w.show();
    return a.exec();
}
