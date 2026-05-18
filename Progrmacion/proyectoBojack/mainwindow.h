#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsScene>

#include <QGraphicsEllipseItem>

#include <QTimer>

#include "nivelEntrenamiento.h"

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

    void actualizarJuego();

private:

    Ui::MainWindow *ui;

    QGraphicsScene *scene;

    QTimer *timer;

    NivelEntrenamiento nivel;

    QGraphicsEllipseItem *jugadorGrafico;

    QGraphicsEllipseItem *discoGrafico;
};

#endif
