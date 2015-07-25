#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gestionxml.h"
#include "lecteur.h"
#include "pattern.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnLire, SIGNAL(clicked()), this, SLOT(onClickBtnLire()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onClickBtnLire()
{
    GestionXML gestionxml;

    Pattern * pattern = new Pattern();

    gestionxml.loadFileIntoPattern("pattern3.xml", pattern);

    Lecteur * lect = new Lecteur();
    lect->setPattern(pattern);

    lect->lirePattern();
}
