#include "lecteur.h"
#include "ui_lecteur.h"
#include "image.h"
#include "vitesse.h"
#include "diaporama.h"

#include <QMessageBox>
#include <QTimer>

#include <iostream>
using namespace std;

// Définition du constructeur de la classe "lecteur"
lecteur::lecteur(QWidget * parent): QMainWindow(parent), ui(new Ui::lecteur) {
    ui -> setupUi(this); // Configuration de l'interface utilisateur

    _numDiaporamaCourant = 0; // Initialisation du numéro de diaporama courant à 0 (le lecteur est vide)

    _timer = new QTimer(this); // Création d'un nouveau timer QTimer

    _timer -> setInterval(2000); // Définition de l'intervalle du timer à 2000 millisecondes (2 secondes)

    // Connexion des signaux et des slots pour les boutons et les actions
    connect(ui -> bSuivant, SIGNAL(clicked()), this, SLOT(arreterModeAutoSuivant()));
    connect(ui -> bPrecedent, SIGNAL(clicked()), this, SLOT(arreterModeAutoPrecedent()));
    connect(ui -> bSuivant, SIGNAL(clicked()), this, SLOT(suivant()));
    connect(ui -> bPrecedent, SIGNAL(clicked()), this, SLOT(precedent()));
    connect(ui -> bDemarrerModeAuto, SIGNAL(clicked()), this, SLOT(demarrerModeAuto()));
    connect(ui -> bArreterModeAuto, SIGNAL(clicked()), this, SLOT(arreterModeAuto()));
    connect(ui -> actionA_propos, SIGNAL(triggered()), this, SLOT(aPropos()));
    connect(ui -> actionQuitter, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui -> actionVitesse, SIGNAL(triggered()), this, SLOT(changerVitesse()));
    connect(ui -> actionCharger_diaporama, SIGNAL(triggered()), this, SLOT(chargerDiaporama()));
    connect(ui -> actionEnlever_diaporama, SIGNAL(triggered()), this, SLOT(viderDiaporama()));

    connect(_timer, SIGNAL(timeout()), this, SLOT(suivant())); // Connexion du signal timeout du timer au slot suivant()
}

// Définition du destructeur de la classe "lecteur"
lecteur::~lecteur() {
    delete ui; // Suppression de l'interface utilisateur
}

// Définition de la fonction "precedent"
void lecteur::precedent() {
    qDebug("precedent appuyé\n"); // Affichage d'un message de débogage

    if (_numDiaporamaCourant != 0) { // Vérification si le diaporama courant n'est pas vide

        if (_posImageCourante > 0) { // Vérification s'il y a une image précédente dans le diaporama
            _posImageCourante--; // Décrémentation de la position de l'image courante

        } else {
            _posImageCourante = nbImages() - 1; // Retour à la fin du diaporama (position de la dernière image)
            qDebug("Retour à la fin du diaporama."); // Affichage d'un message de débogage
        }

        cout << "Image " << _posImageCourante << " affichee." << endl; // Affichage de l'index de l'image courante
        cout << "Titre : " << imageCourante() -> getTitre() << endl; // Affichage du titre de l'image courante

        QString chemin = QString::fromStdString(imageCourante() -> getChemin()); // Conversion du chemin de l'image courante en QString
        QPixmap image(chemin); // Chargement de l'image à partir du chemin

        // Mise à jour des éléments de l'interface utilisateur avec les informations de l'image courante
        ui -> l_intitulediapositive -> setText(QString::fromStdString(imageCourante() -> getTitre()));  // Définit le texte de l'intitulé de la diapositive avec le titre de l'image courante
        ui -> l_chemin -> setText(QString::fromStdString(imageCourante() -> getChemin()));  // Définit le texte de l'indicateur de chemin avec le chemin de l'image courante
        ui -> l_rang -> setText(QString::number(imageCourante() -> getRang()));  // Définit le texte de l'indicateur de rang avec le rang de l'image courante
        ui -> l_cat -> setText(QString::fromStdString(imageCourante() -> getCategorie()));  // Définit le texte de l'indicateur de catégorie avec la catégorie de l'image courante

        // Récupère la largeur et la hauteur de l'image
        int w = image.width();
        int h = image.height();
        // Redimensionne l'image pour qu'elle s'adapte à la taille de la fenêtre tout en conservant son ratio
        ui->l_image->setPixmap(image.scaled(w, h, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

        imageCourante()->afficher();  // Affiche les informations de l'image courante
    }
}

void lecteur::suivant() {
    qDebug("suivant appuyé\n");  // Affiche un message de débogage indiquant que le bouton "suivant" a été pressé

    if (_numDiaporamaCourant != 0) {

        if (getNumDiaporamaCourant() > 0 && _posImageCourante < nbImages() - 1) {
            _posImageCourante++;
            imageCourante() -> afficher();  // Appelle la méthode afficher() de l'image courante pour afficher ses informations
        } else {
            _posImageCourante = 0;
            cout << "Impossible d'avancer : fin du diaporama atteinte" << endl;  // Affiche "Impossible d'avancer : fin du diaporama atteinte" dans la console
        }

        cout << "Image " << _posImageCourante << " affichee." << endl;  // Affiche "Image <numéro de l'image> affichee." dans la console
        cout << "Titre : " << imageCourante() -> getTitre() << endl;  // Affiche le titre de l'image courante dans la console

        QString chemin = QString::fromStdString(imageCourante() -> getChemin());  // Convertit le chemin de l'image courante en QString
        QPixmap image(chemin);  // Charge l'image à partir du chemin

        ui -> l_intitulediapositive -> setText(QString::fromStdString(imageCourante() -> getTitre()));  // Définit le texte de l'intitulé de la diapositive avec le titre de l'image courante
        ui -> l_chemin -> setText(QString::fromStdString(imageCourante() -> getChemin()));  // Définit le texte de l'indicateur de chemin avec le chemin de l'image courante
        ui -> l_rang -> setText(QString::number(imageCourante() -> getRang()));  // Définit le texte de l'indicateur de rang avec le rang de l'image courante
        ui -> l_cat -> setText(QString::fromStdString(imageCourante() -> getCategorie()));  // Définit le texte de l'indicateur de catégorie avec la catégorie de l'image courante

        // Récupère la largeur et la hauteur de l'image
        int w = image.width();
        int h = image.height();
        // Redimensionne l'image pour l'adapter à une fenêtre de taille w x h tout en conservant son ratio
        ui -> l_image -> setPixmap(image.scaled(w, h, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    }
}


void lecteur::demarrerModeAuto() {
    qDebug("demarrer appuyé\n");  // Affiche un message de débogage indiquant que le bouton "Démarrer" a été pressé

    if (_numDiaporamaCourant != 0) {

        ui -> statusbar -> showMessage("Mode auto actif");  // Affiche le message "Mode auto actif" dans la barre de statut

        _posImageCourante = 0;  // Réinitialise la position de l'image courante à 0

        if (!_modeAuto) {
            _modeAuto = true;
            qDebug("Bouton Démarrer le mode auto appuyé.");  // Affiche un message de débogage indiquant que le bouton "Démarrer le mode auto" a été pressé
        }

        _timer -> stop();  // Arrête le timer (s'il était déjà en cours)
        _timer -> start();  // Démarre le timer

        QString chemin = QString::fromStdString(imageCourante() -> getChemin());  // Convertit le chemin de l'image courante en QString
        QPixmap image(chemin);  // Charge l'image à partir du chemin

        ui -> l_intitulediapositive -> setText(QString::fromStdString(imageCourante() -> getTitre()));  // Définit le texte de l'intitulé de la diapositive avec le titre de l'image courante
        ui -> l_chemin -> setText(QString::fromStdString(imageCourante() -> getChemin()));  // Définit le texte de l'indicateur de chemin avec le chemin de l'image courante
        ui -> l_rang -> setText(QString::number(imageCourante() -> getRang()));  // Définit le texte de l'indicateur de rang avec le rang de l'image courante
        ui -> l_cat -> setText(QString::fromStdString(imageCourante() -> getCategorie()));  // Définit le texte de l'indicateur de catégorie avec la catégorie de l'image courante

        // Récupère la largeur et la hauteur de l'image
        int w = image.width();
        int h = image.height();
        // Redimensionne l'image pour l'adapter à une fenêtre de taille w x h tout en conservant son ratio
        ui -> l_image -> setPixmap(image.scaled(w, h, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

        imageCourante() -> afficher();  // Appelle la méthode afficher() de l'image courante pour afficher ses informations
    }
}


void lecteur::arreterModeAuto() {
    qDebug("arreter appuyé\n");  // Affiche un message de débogage indiquant que le bouton "Arrêter" a été pressé

    if (_numDiaporamaCourant != 0) {

        if (_modeAuto) {
            ui -> statusbar -> showMessage("Mode manuel actif");  // Affiche le message "Mode manuel actif" dans la barre de statut
            _modeAuto = false;
            qDebug("arretermodeauto");  // Affiche un message de débogage indiquant que le mode automatique a été arrêté
            _timer -> stop();  // Arrête le timer
        }
    }
}


void lecteur::arreterModeAutoSuivant() {
    if (_modeAuto) {
        ui -> statusbar -> showMessage("Mode manuel actif");  // Affiche le message "Mode manuel actif" dans la barre de statut
        _modeAuto = false;
        qDebug("arretermodeauto");  // Affiche un message de débogage indiquant que le mode automatique a été arrêté
        _timer -> stop();  // Arrête le timer
        precedent();  // Appelle la fonction precedent() pour passer à l'image précédente
    }
}


void lecteur::arreterModeAutoPrecedent() {
    if (_modeAuto) {
        ui -> statusbar -> showMessage("Mode manuel actif");  // Affiche le message "Mode manuel actif" dans la barre de statut
        _modeAuto = false;
        qDebug("arretermodeauto");  // Affiche un message de débogage indiquant que le mode automatique a été arrêté
        _timer -> stop();  // Arrête le timer
        suivant();  // Appelle la fonction suivant() pour passer à l'image suivante
    }
}


void lecteur::afficher() {
    // Affiche si le lecteur est vide ou affiche le numéro du diaporama courant
    if (getNumDiaporamaCourant() == 0) {
        cout << "Lecteur vide." << endl;  // Affiche "Lecteur vide." si le lecteur est vide
    } else {
        cout << "Diaporama numéro " << getNumDiaporamaCourant() << " est en cours de lecture." << endl;  // Affiche le numéro du diaporama courant

        // Affiche l'image courante si elle existe, sinon affiche "diaporama vide"
        if (nbImages() > 0) {
            Image * imageCourante = _diaporama[_posImageCourante];
            cout << "Image courante : ";
            imageCourante -> afficher();  // Affiche l'image courante
            cout << endl;
        } else {
            cout << "Diaporama vide." << endl;  // Affiche "Diaporama vide." si le diaporama est vide
        }
    }
}


unsigned int lecteur::nbImages() {
    return _diaporama.size();  // Retourne le nombre d'images dans le diaporama
}

Image * lecteur::imageCourante() {
    return _diaporama[_posImageCourante];  // Retourne l'image courante dans le diaporama
}

unsigned int lecteur::getNumDiaporamaCourant() {
    return _numDiaporamaCourant;  // Retourne le numéro du diaporama courant
}

void lecteur::aPropos() {
    QMessageBox::information(this, "A propos", "Version : 6\nDate de création : 9/06/2023\nAuteurs : Grigori Gratchev & Lucas Crussière");// Affiche une boîte de dialogue d'information contenant les informations sur l'application
}

void lecteur::changerDiaporama(unsigned int pNumDiaporama) {
    // S'il y a un diaporama courant, le vider, puis charger le nouveau diaporama
    if (getNumDiaporamaCourant() > 0) {
        viderDiaporama();  // Vide le diaporama courant
    }
    _numDiaporamaCourant = pNumDiaporama;  // Affecte le numéro du nouveau diaporama courant
    if (getNumDiaporamaCourant() > 0) {
        chargerDiaporama();  // Charge le diaporama courant
    } else {
        cout << "non chargé\n";  // Affiche "non chargé" si le diaporama n'a pas été chargé
    }
}


void lecteur::chargerDiaporama() {
    viderDiaporama(); // Vider le diaporama afin de ne pas avoir les images de plusieurs diaporamas chargées en même temps dans le lecteur

    // Affiche un message dans la barre de statut
    ui->statusbar->showMessage("Mode manuel actif");

    // Affiche un message de débogage
    qDebug("Charger diapo appuyé\n");

    // Ouvre la base de données
    _bddSAE->openDataBase();


    _posImageCourante = 0; // Initialise la position de l'image courante à 0


    // Crée une fenêtre de dialogue pour choisir le diaporama
    Diaporama *choisirDiaporama = new Diaporama(nullptr);
    choisirDiaporama->exec();

    // Récupère le numéro du diaporama choisi par l'utilisateur depuis la fenêtre de dialogue
    _numDiaporamaCourant = choisirDiaporama->getDiaporamaChoisi();


    // Requête SQL pour sélectionner les informations des diapositives du diaporama courant
    QString texteRequete = "SELECT DiaposDansDiaporama.rang, Diapos.uriPhoto, Familles.nomFamille, Diapos.titrePhoto FROM DiaposDansDiaporama JOIN Diaporamas ON DiaposDansDiaporama.idDiaporama = Diaporamas.idDiaporama JOIN Diapos ON DiaposDansDiaporama.idDiapo = Diapos.idphoto JOIN Familles ON Diapos.idFam = Familles.idFamille WHERE DiaposDansDiaporama.idDiaporama = :id";

    // Exécute la requête SQL et récupère le résultat
    QSqlQuery requete;
    requete.prepare(texteRequete);
    requete.bindValue(":id", _numDiaporamaCourant);
    requete.exec();
    QSqlRecord resultat = requete.record();

    // Parcourt le résultat de la requête et crée les objets Image correspondants, puis les ajoute au diaporama
    for (int i = 0; requete.next(); i++) {
        Image *imageACharger = new Image(requete.value(0).toInt(), requete.value(2).toString().toStdString(), requete.value(3).toString().toStdString(), ":" + requete.value(1).toString().toStdString());
        _diaporama.push_back(imageACharger);
    }

    // Trie le contenu du diaporama par ordre croissant selon le rang de l'image dans le diaporama
    for (unsigned int i = 1; i < nbImages(); i++) {
        Image *image = _diaporama[i];
        int j = i - 1;
        while (j >= 0 && _diaporama[j]->getRang() > image->getRang()) {
            _diaporama[j + 1] = _diaporama[j];
            j--;
        }
        _diaporama[j + 1] = image;
    }



    // Récupère le chemin de l'image courante
    QString chemin = QString::fromStdString(imageCourante()->getChemin());

    // Charge l'image à partir du chemin
    QPixmap image(chemin);

    // Affiche les informations de l'image courante dans les éléments de l'interface utilisateur
    ui->l_intitulediapositive->setText(QString::fromStdString(imageCourante()->getTitre()));
    ui->l_chemin->setText(QString::fromStdString(imageCourante()->getChemin()));
    ui->l_rang->setText(QString::number(imageCourante()->getRang()));
    ui->l_cat->setText(QString::fromStdString(imageCourante()->getCategorie()));

    // Récupère les dimensions de l'image
    int w = image.width();
    int h = image.height();

    // Redimensionne l'image pour s'adapter à la fenêtre tout en conservant son rapport d'aspect
    ui->l_image->setPixmap(image.scaled(w, h, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

    // Affiche un message indiquant le numéro du diaporama courant et le nombre d'images chargées
    cout << "Diaporama num. " << getNumDiaporamaCourant() << " selectionne. " << endl;
    cout << nbImages() << " images chargees dans le diaporama" << endl;


    // Requête SQL pour sélectionner le titre du diaporama courant
    QString texteRequeteTitre = "SELECT `titre Diaporama` FROM Diaporamas WHERE idDiaporama = :id;";

    QSqlQuery requeteTitre;
    requeteTitre.prepare(texteRequeteTitre);
    requeteTitre.bindValue(":id", _numDiaporamaCourant);
    requeteTitre.exec();

    if (requeteTitre.next()) {
        QString titre = requeteTitre.value(0).toString();
        qDebug() << "Titre : " << titre;
    } else {
        qDebug() << "Aucun résultat trouvé.";
    }
    ui -> l_titrediaporama -> setText(requeteTitre.value(0).toString());

    // Requête SQL pour sélectionner la vitesse du diaporama courant
    QString texteRequeteVitesse = "SELECT vitesseDefilement FROM Diaporamas WHERE idDiaporama = :id;";

    QSqlQuery requeteVitesse;
    requeteVitesse.prepare(texteRequeteVitesse);
    requeteVitesse.bindValue(":id", _numDiaporamaCourant);
    requeteVitesse.exec();
    int vitesse = 0;

    if (requeteVitesse.next()) {
        vitesse = requeteVitesse.value(0).toInt() * 1000;
        qDebug() << "Vitesse : " << vitesse;
    } else {
        qDebug() << "Aucun résultat trouvé.";
    }

    _timer->setInterval(vitesse);
}


void lecteur::viderDiaporama() {
    // Vérifie si un diaporama est en cours
    if (_numDiaporamaCourant != 0) {
        qDebug("vider diapo appuyé\n");

        // Vérifie s'il y a des images dans le diaporama
        if (nbImages() > 0) {
            qDebug("nbImages > 0\n");

            // Supprime toutes les images du diaporama
            unsigned int taille = nbImages();
            for (unsigned int i = 0; i < taille; i++) {
                _diaporama.pop_back();
            }

            // Réinitialise les variables de position et de numéro du diaporama courant
            _posImageCourante = 0;
            _numDiaporamaCourant = 0;

            // Réinitialise les éléments de l'interface utilisateur liés à l'image courante
            ui->l_intitulediapositive->setText("");
            ui->l_chemin->setText("");
            ui->l_rang->setText("");
            ui->l_cat->setText("");
            ui->l_image->clear();
        }

        // Affiche le nombre d'images restantes dans le diaporama
        cout << nbImages() << " images restantes dans le diaporama." << endl;
    }
}

void lecteur::changerVitesse() {
    // Crée une fenêtre de dialogue pour changer la vitesse
    Vitesse *changerVitesse = new Vitesse(nullptr);
    changerVitesse->exec();

    // Récupère la vitesse choisie par l'utilisateur depuis la fenêtre de dialogue
    int vitesseChoisie = changerVitesse->getVitesseChoisie();

    // Modifie l'intervalle du timer avec la nouvelle vitesse
    _timer->setInterval(vitesseChoisie);

    // Affiche la nouvelle vitesse dans la console
    cout << "vitesse " << vitesseChoisie << endl;
}

