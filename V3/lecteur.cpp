#include "lecteur.h"
#include "ui_lecteur.h"
#include <QMessageBox>
#include "image.h"
#include <iostream>
#include <QTimer>

using namespace std;

lecteur::lecteur(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::lecteur)
{
    ui->setupUi(this);

    _numDiaporamaCourant = 0;   // =  le lecteur est vide
    chargerDiaporama();

    _timer = new QTimer(this);
    _timer->setInterval(2000);

    /*connect(ui->bPrecedent,SIGNAL(clicked()), this, SLOT(precedent()));
    connect(ui->bSuivant,SIGNAL(clicked()), this, SLOT(suivant()));*/




    connect(ui->bSuivant,SIGNAL(clicked()), this, SLOT(arreterModeAutoSuivant()));
    connect(ui->bPrecedent,SIGNAL(clicked()), this, SLOT(arreterModeAutoPrecedent()));
    connect(ui->bSuivant,SIGNAL(clicked()), this, SLOT(suivant()));
    connect(ui->bPrecedent,SIGNAL(clicked()), this, SLOT(precedent()));
    connect(ui->bDemarrerModeAuto,SIGNAL(clicked()), this, SLOT(demarrerModeAuto()));
    connect(ui->bArreterModeAuto,SIGNAL(clicked()), this, SLOT(arreterModeAuto()));
    connect(ui->actionA_propos,SIGNAL(triggered()), this, SLOT(aPropos()));
    connect(ui->actionQuitter,SIGNAL(triggered()), this, SLOT(close()));

    connect(_timer, SIGNAL(timeout()), this, SLOT(suivant()));
}

lecteur::~lecteur()
{
    delete ui;
}

void lecteur::precedent(){

    if (_posImageCourante > 0)
        {
            _posImageCourante--;
            cout << "Image precedente" << endl;
        }
        else
        {
            _posImageCourante = nbImages() - 1; // retourne à la fin du diaporama
            qDebug("Retour à la fin du diaporama.");
        }

        cout << "Image " << _posImageCourante << " affichee." << endl;
        cout << "Titre : " << imageCourante()->getTitre() << endl;


        QString chemin = QString::fromStdString(imageCourante()->getChemin());
        QPixmap image (chemin);

        ui->l_intitulediapositive->setText(QString::fromStdString(imageCourante()->getTitre()));
        ui->l_chemin->setText(QString::fromStdString(imageCourante()->getChemin()));
        ui->l_rang->setText(QString::number(imageCourante()->getRang()));
        ui->l_cat->setText(QString::fromStdString(imageCourante()->getCategorie()));
        int w = image.width();
        int h = image.height();
        // set a scaled pixmap to a w x h window keeping its aspect ratio
        ui->l_image->setPixmap(image.scaled(w,h,Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

        imageCourante()->afficher();
}


void lecteur::suivant(){

    if (getNumDiaporamaCourant() > 0 && _posImageCourante < nbImages() - 1){
        _posImageCourante++;
       cout << "Image suivante" << endl;
       imageCourante()->afficher();
    }

        else {
        _posImageCourante = 0;
            cout << "Impossible d'avancer : fin du diaporama atteinte" << endl;
           cout << "num diapo courant : " << getNumDiaporamaCourant() << endl << "posi image courante : " << _posImageCourante << endl << "nb d'images - 1 : " << nbImages() - 1 << endl;
        }

    cout << "Image " << _posImageCourante << " affichee." << endl;
    cout << "Titre : " << imageCourante()->getTitre() << endl;


    QString chemin = QString::fromStdString(imageCourante()->getChemin());
    QPixmap image (chemin);

    ui->l_intitulediapositive->setText(QString::fromStdString(imageCourante()->getTitre()));
    ui->l_chemin->setText(QString::fromStdString(imageCourante()->getChemin()));
    ui->l_rang->setText(QString::number(imageCourante()->getRang()));
    ui->l_cat->setText(QString::fromStdString(imageCourante()->getCategorie()));



    int w = image.width();
    int h = image.height();
    // set a scaled pixmap to a w x h window keeping its aspect ratio
    ui->l_image->setPixmap(image.scaled(w,h,Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
}


void lecteur::demarrerModeAuto()
{
     _posImageCourante = 0;
    if (!_modeAuto)
    {
        _modeAuto = true;
        qDebug("Bouton Démarrer le mode auto appuyé.");
    }

    _timer->stop();
    _timer->start();

    QString chemin = QString::fromStdString(imageCourante()->getChemin());
    QPixmap image(chemin);

    ui->l_intitulediapositive->setText(QString::fromStdString(imageCourante()->getTitre()));
    ui->l_chemin->setText(QString::fromStdString(imageCourante()->getChemin()));
    ui->l_rang->setText(QString::number(imageCourante()->getRang()));
    ui->l_cat->setText(QString::fromStdString(imageCourante()->getCategorie()));
    int w = image.width();
    int h = image.height();
    // set a scaled pixmap to a w x h window keeping its aspect ratio
    ui->l_image->setPixmap(image.scaled(w,h,Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

    imageCourante()->afficher();
}


void lecteur::arreterModeAuto(){
    if(_modeAuto){
    _modeAuto = false;
    qDebug("arretermodeauto");
    _timer->stop();
    }
}

void lecteur::arreterModeAutoSuivant(){
    if(_modeAuto){
    _modeAuto = false;
    qDebug("arretermodeauto");
    _timer->stop();
    precedent();
    }
}

void lecteur::arreterModeAutoPrecedent(){
    if(_modeAuto){
    _modeAuto = false;
    qDebug("arretermodeauto");
    _timer->stop();
    suivant();
    }
}

void lecteur::afficher()
{
    // afficher si le lecteur est vide ou afficher le numéro du diaporama courant
        if (getNumDiaporamaCourant() == 0)
        {
            cout << "Lecteur vide." << endl;
        }
        else
        {
            cout << "Diaporama numéro " << getNumDiaporamaCourant() << " est en cours de lecture." << endl;

            // afficher l'image courante si elle existe, sinon afficher "diaporama vide"
            if (nbImages() > 0)
            {
                Image* imageCourante = _diaporama[_posImageCourante];
                cout << "Image courante : " ;
                imageCourante->afficher();
                cout << endl;
            }
            else
            {
                cout << "Diaporama vide." << endl;
            }
        }
}

unsigned int lecteur::nbImages()
{
    return _diaporama.size();
}

Image *lecteur::imageCourante()
{
    return _diaporama[_posImageCourante];
}

unsigned int lecteur::getNumDiaporamaCourant()
{
    return _numDiaporamaCourant;
}

void lecteur::aPropos()
{
   QMessageBox::information(this, "A propos", "Version : 3\nDate de création : 16/05/2023\nAuteurs : Grigori Gratchev & Lucas Crussière");
}

void lecteur::changerDiaporama(unsigned int pNumDiaporama)
{
    // s'il y a un diaporama courant, le vider, puis charger le nouveau Diaporama
    if (getNumDiaporamaCourant() > 0)
    {
        viderDiaporama();
    }
    _numDiaporamaCourant = pNumDiaporama;
    if (getNumDiaporamaCourant() > 0)
    {
        chargerDiaporama(); // charge le diaporama courant
    }
    else
    {
        cout<< "non chargé\n";
    }

}

void lecteur::chargerDiaporama()
{

    Image* imageACharger;
    imageACharger = new Image(3, "personne", "Blanche Neige", "\\\\haya\\dossiersetud_BaieSsd\\ggratchev\\Downloads\\cartesDisney\\Disney_4.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(2, "personne", "Cendrillon", "\\\\haya\\dossiersetud_BaieSsd\\ggratchev\\Downloads\\cartesDisney\\Disney_2.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(4, "animal", "Pluto", "\\\\haya\\dossiersetud_BaieSsd\\ggratchev\\Downloads\\cartesDisney\\Disney_30.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(1, "animal", "Donald", "\\\\haya\\dossiersetud_BaieSsd\\ggratchev\\Downloads\\cartesDisney\\Disney_8.gif");
    _diaporama.push_back(imageACharger);


     // trier le contenu du diaporama par ordre croissant selon le rang de l'image dans le diaporama
    for (unsigned int i = 1; i < nbImages(); i++)
        {
            Image* image = _diaporama[i];
            int j = i - 1;
            while (j >= 0 && _diaporama[j]->getRang() > image->getRang())
            {
                _diaporama[j+1] = _diaporama[j];
                j--;
            }
            _diaporama[j+1] = image;
        }

     _posImageCourante = 0;
     _numDiaporamaCourant = 1;

     QString chemin = QString::fromStdString(imageCourante()->getChemin());
     QPixmap image (chemin);

     ui->l_intitulediapositive->setText(QString::fromStdString(imageCourante()->getTitre()));
     ui->l_chemin->setText(QString::fromStdString(imageCourante()->getChemin()));
     ui->l_rang->setText(QString::number(imageCourante()->getRang()));
     ui->l_cat->setText(QString::fromStdString(imageCourante()->getCategorie()));

     int w = image.width();
     int h = image.height();
     // set a scaled pixmap to a w x h window keeping its aspect ratio
     ui->l_image->setPixmap(image.scaled(w,h,Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
     cout << "Diaporama num. " << getNumDiaporamaCourant() << " selectionne. " << endl;
     cout << nbImages() << " images chargees dans le diaporama" << endl;

}
void lecteur::viderDiaporama()
{
    if (nbImages () > 0)
    {
        unsigned int taille = nbImages();
        for (unsigned int i = 0; i < taille ; i++)
        {
            _diaporama.pop_back();
        }
     _posImageCourante = 0;
    }
    cout << nbImages() << " images restantes dans le diaporama." << endl;

}
