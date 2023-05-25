#include "lecteurvue.h"
#include "ui_lecteurvue.h"

lecteurvue::lecteurvue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::lecteurvue)
{
    ui->setupUi(this);
}

lecteurvue::~lecteurvue()
{
    delete ui;
}

