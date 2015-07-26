#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gestionxml.h"
#include "lecteur.h"
#include "pattern.h"

#include <QFileDialog>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    lecteur(0),
    pattern(0),
    gestionXml(0)
{
    ui->setupUi(this);

    lecteur = new Lecteur;
    gestionXml = new GestionXML;

    connect(ui->btnLire, SIGNAL(clicked()), this, SLOT(onClickBtnLire()));
    connect(ui->btnArreter, SIGNAL(clicked()), this, SLOT(onClickBtnArreter()));
    connect(ui->btnSelectPattern, SIGNAL(clicked()), this, SLOT(onClickBtnSelectFile()));
    connect(ui->spinBoxTempo, SIGNAL(valueChanged(int)), this, SLOT(onTempoChanged(int)));
    connect(ui->btnQuitter, SIGNAL(clicked()), this, SLOT(close()));
    connect(lecteur, SIGNAL(currentTempsChanged(int)), ui->sliderProgression, SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onClickBtnLire()
{
    if (lecteur->getPattern()) {
        lecteur->lire();
    } else {
        std::cout<<"Aucun pattern chargé"<<std::endl;
    }
}

void MainWindow::onClickBtnArreter()
{
    lecteur->arreter();
    ui->sliderProgression->setValue(0);
}

void MainWindow::onClickBtnSelectFile()
{
    QString fichier = QFileDialog::getOpenFileName(this, tr("Choisir fichier"), ".", tr("Fichiers XML (*.xml)"));
    if ( ! fichier.isNull()) {
        pattern = new Pattern;
        if (gestionXml->loadFileIntoPattern(fichier.toStdString().c_str(), pattern) )
        {
            lecteur->setPattern(pattern);
            ui->lineEditFile->setText(fichier);
            ui->spinBoxTempo->setValue(pattern->getTempo());
            ui->sliderProgression->setMaximum(pattern->getNbTemps()-1);
            std::cout<<"Fichier chargé en Pattern : "<<fichier.toStdString().c_str()<<std::endl;
        }
    }
}

void MainWindow::onTempoChanged(int value)
{
    if (pattern) {
        pattern->setTempo(value);
    }
}
