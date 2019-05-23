#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QtCore>
#include <QtGui>
#include "rectangulo.h"
#include "hormiga.h"
#include "cuadro.h"
#include "dialog.h"
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothsocket.h>
#include <QListWidget>





namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
private slots:
    void on_StartButton_clicked();
    void on_StopButton_clicked();

    int getNewman(int i, int j, int crit);
    bool NewmanOffset(int i, int j, int crit, int orien);
    bool dep(int i, int j, int crit);

    int random();
    int randomOffset();

    void newGeneration();
    void evaluar();

    void updateDimension();
    void actualiza(int i, int j,int orientacion);

    void on_colorButton_clicked();
    void on_dimButton_clicked();
    void on_fileButton_clicked();
    void on_salvaButton_clicked();

    void updateGraphic();

    void on_OffB_clicked();
    void deviceDiscovered( const QBluetoothDeviceInfo &device );


    void timerGeneral(int a);
    void Cambio();


    void on_ListaV_itemClicked(QListWidgetItem *item);
    void on_checkHormiga_clicked();
    void on_pushButton_clicked();
    void rastreo();

    void on_AcercaB_clicked();

    void on_vola_clicked();

    void on_volb_clicked();

    void on_pushButton_2_clicked();

    void on_Comportamiento_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Dialog *nuevoD;
    Cuadro *cuadN;

    Rectangulo **recta;
    Hormiga *hormiga;
    int **aux;    
    int ** min;
    int **val;
    int cont;

    int dimension;

    QTimer* timer;
    QTimer* listen;
    QTimer* rastre;
    QTime time;
    QBrush* color;

    int xInit,yInit;    
    int incre, stateActive,stateSemiActive,stateNutrient,stateExplore,stateSpace,stateExpand, mayor;
    int Caso;
    double dm;

    QVector<double> x,y,y2,y3,y4,y5,y6;

    QBluetoothDeviceDiscoveryAgent *agent = new QBluetoothDeviceDiscoveryAgent;
    QBluetoothSocket *socket;
    QString string;

    int zoomint,zoomcontrol;

    int coordx,coory;
    int Bcoordx,Bcoory;

protected:

    bool eventFilter(QObject *target, QEvent *event);


};

#endif // MAINWINDOW_H
