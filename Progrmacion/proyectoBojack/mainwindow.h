#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "juego.h"
#include <QKeyEvent>

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

    void volverMenu();



private:

    Ui::MainWindow *ui;

    QGraphicsScene *scene;

    Juego *juego;
    QMediaPlayer *musicaMenu;
    QMediaPlayer *musicaNivel1;
    QMediaPlayer *musicaNivel2;

    QAudioOutput *audioMenu;
    QAudioOutput *audioNivel1;
    QAudioOutput *audioNivel2;

    bool enNivel;
    int nivelActual;
    bool cargando;

protected:

    void keyPressEvent(
        QKeyEvent* event
        ) override;

};

#endif
