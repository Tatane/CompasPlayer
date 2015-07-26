#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "lecteur.h"
#include "gestionxml.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onClickBtnLire();
    void onClickBtnArreter();
    void onClickBtnSelectFile();
    void onTempoChanged(int value);

private:
    Ui::MainWindow *ui;
    Lecteur * lecteur;
    Pattern * pattern;
    GestionXML * gestionXml;
};

#endif // MAINWINDOW_H
