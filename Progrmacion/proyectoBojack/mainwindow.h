#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "juego.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();


private slots:

    void iniciarNivel1();

    void iniciarNivel2();


private:

    Ui::MainWindow *ui;

    QGraphicsScene *scene;

    Juego *juego;
    QMediaPlayer *musicaMenu;

    QAudioOutput *audioOutput;
};

#endif
