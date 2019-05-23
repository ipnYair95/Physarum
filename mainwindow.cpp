#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QFileDialog>
#include <QList>
#include <algorithm>
#include <QtBluetooth>
#include <QListWidget>
#include "cuadro.h"
#include <QtMath>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    timer(new QTimer(this)),
    ui(new Ui::MainWindow)
{

    QDateTime cd = QDateTime::currentDateTime();
    Caso = false;


    rastre = new QTimer();

    timer->setInterval(1);
    rastre->setInterval(1000);

    ui->setupUi(this);        

    //connect(agent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));
    connect(timer, SIGNAL(timeout()), this, SLOT(evaluar()));
    //connect(rastre, SIGNAL(timeout()), this, SLOT(rastreo()));
    connect( ui->SliderTime, SIGNAL(valueChanged(int)),this,SLOT(timerGeneral(int)) );
    //connect( ui->Comportamiento, SIGNAL(clicked()),this,SLOT(Cambio()));


    dimension = 4;
    qsrand( cd.toTime_t());

    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

    updateDimension();
    //agent->start();


    ui->generationLabel->setText( "  T =  " + QString::number(0)
                                            + " - Q<sub>1</sub> = " + QString::number(0)
                                            + " - Q<sub>4</sub> = " + QString::number(0)
                                            + " - Q<sub>5</sub> = " + QString::number(0)
                                            + " - Q<sub>7</sub> = " + QString::number(0)
                                            + " - Q<sub>8</sub> = " + QString::number(0)
                                );


    zoomcontrol = 50;

    /*ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicWidget->setBackground(QColor(0, 0, 0, 255));
    ui->graphicWidget->xAxis->setTickLabelColor(Qt::white);
    ui->graphicWidget->xAxis->setBasePen(QPen(Qt::white));
    ui->graphicWidget->xAxis->setLabelColor(Qt::white);
    ui->graphicWidget->xAxis->setTickPen(QPen(Qt::white));
    ui->graphicWidget->xAxis->setSubTickPen(QPen(Qt::white));

    ui->graphicWidget->yAxis->setTickLabelColor(Qt::white);
    ui->graphicWidget->yAxis->setBasePen(QPen(Qt::white));
    ui->graphicWidget->yAxis->setLabelColor(Qt::white);
    ui->graphicWidget->yAxis->setTickPen(QPen(Qt::white));
    ui->graphicWidget->yAxis->setSubTickPen(QPen(Qt::white));
    */


    QPixmap pixmap("play.png"),pixmap2("stop.png"),pixmap3("open.png"),pixmap4("save.png"),pixmap5("ok.png");
    QPixmap pixmap6("up.png"),pixmap7("down.png"),pixmap8("off.png"),pixmap9("about.png");
    QIcon ButtonIcon(pixmap),ButtonIcon2(pixmap2),ButtonIcon3(pixmap3),ButtonIcon4(pixmap4),ButtonIcon5(pixmap5);
    QIcon ButtonIcon6(pixmap6),ButtonIcon7(pixmap7),ButtonIcon8(pixmap8),ButtonIcon9(pixmap9);

    ui->StartButton->setIcon(ButtonIcon);
    ui->StartButton->setIconSize(QSize(25,25));

    ui->StopButton->setIcon(ButtonIcon2);
    ui->StopButton->setIconSize(QSize(25,25));

    ui->fileButton->setIcon(ButtonIcon3);
    ui->fileButton->setIconSize(QSize(25,25));

    ui->salvaButton->setIcon(ButtonIcon4);
    ui->salvaButton->setIconSize(QSize(25,25));

    ui->colorButton->setIcon(ButtonIcon5);
    ui->colorButton->setIconSize(QSize(25,25));

    ui->dimButton->setIcon(ButtonIcon5);
    ui->dimButton->setIconSize(QSize(25,25));

    ui->vola->setIcon(ButtonIcon6);
    ui->vola->setIconSize(QSize(25,25));

    ui->volb->setIcon(ButtonIcon7);
    ui->volb->setIconSize(QSize(25,25));

    ui->pushButton->setIcon(ButtonIcon);
    ui->pushButton->setIconSize(QSize(25,25));

    ui->pushButton_2->setIcon(ButtonIcon5);
    ui->pushButton_2->setIconSize(QSize(25,25));

    ui->OffB->setIcon(ButtonIcon2);
    ui->OffB->setIconSize(QSize(25,25));

    ui->AcercaB->setIcon(ButtonIcon9);
    ui->AcercaB->setIconSize(QSize(90,90));

    ui->Comportamiento->setIcon(ButtonIcon8);

    QPixmap pixmapTarget = QPixmap("clock.png");
    pixmapTarget = pixmapTarget.scaled(30,30, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_8->setPixmap(pixmapTarget );

    QPixmap pixmapTarget2 = QPixmap("blue.png");
    pixmapTarget2 = pixmapTarget2.scaled(30,30, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_7->setPixmap(pixmapTarget2 );

    QPixmap bkgnd("phy.jpg");
       bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
       QPalette palette;
       palette.setBrush(QPalette::Background, bkgnd);
       this->setPalette(palette);


    ui->Comportamiento->setIconSize(QSize(50, 50));
    cont = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
    connect( agent, SIGNAL( deviceDiscovered( QBluetoothDeviceInfo ) ) , this , SLOT ( deviceDiscovered( QBluetoothDeviceInfo ) ) );
    agent->start();

}

void MainWindow::evaluar()
{

    incre++;
    stateActive = 0;
    stateNutrient = 0;
    stateExplore = 0;
    stateSpace = 0;
    stateSemiActive = 0;
    stateExpand = 0;


    for(int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
            aux[i][j] = recta[i][j].getEdo();
            if(  recta[i][j].getEdo() == 3 )
            {
                val[i][j] = incre+1;
            }

        }
    }

    //QDebug dbg(QtDebugMsg);

    /*

      getNewman(): Its objetive is to know how many represents of some state are
      in the neighrborhood.

      NewmanOffset(): It's used to know if there is some valid cell in the direction
      selected according to rule 5

      dep(): As it was mentioned in the article, this function is to know if
      there is any cell that depends on the reference cell. If there is dependency
      the will be true

      randonOffset(): can the cell born?


    */

    for( int i = 0; i < dimension; i++)
    {

        for(int j = 0; j < dimension; j++)
        {


            switch( recta[i][j].getEdo() )
            {

                case 0:  // Free Space

                        //deterministic
                        //if( min[i][j] == 0 &&  ( getNewman(i,j,4) != 0 || getNewman(i,j,3) != 0 || getNewman(i,j,6) != 0)  )
                        //non-deterministic
                        if( min[i][j] == 0 && (randomOffset() + 1) < 3 && ( getNewman(i,j,4) != 0 || getNewman(i,j,3) != 0 || getNewman(i,j,6) != 0)  )
                        {
                            aux[i][j] = 7;
                            cont++;
                            val[i][j] = cont;
                        }
                        stateSpace++;
                break;

                case 1: // non-found nutrient

                        if( getNewman(i,j,5) != 0 || getNewman(i,j,6) != 0)
                        {
                            aux[i][j] = 6;
                        }
                        stateNutrient++;
                break;

                case 4: // gel in evaluation
                        if( Caso )   // evaluation with q0 "continuos exploration"
                        {
                            if(  getNewman(i,j,7) == 0)
                            {

                                  int d1 = val[i][j+1];
                                  int d2 = val[i-1][j];
                                  int d3 = val[i][j-1];
                                  int d4 = val[i+1][j];

                                  QVector<int> tempo;

                                  if( recta[i][j+1].getEdo() == 3 || recta[i][j+1].getEdo() == 5 || recta[i][j+1].getEdo() == 6 )
                                  {
                                      tempo.push_front(d1);
                                  }
                                  if( recta[i-1][j].getEdo() == 3 || recta[i-1][j].getEdo() == 5 || recta[i-1][j].getEdo() == 6 )
                                  {
                                       tempo.push_front(d2);
                                  }
                                  if( recta[i][j-1].getEdo() == 3 || recta[i][j-1].getEdo() == 5 || recta[i][j-1].getEdo() == 6 )
                                  {
                                       tempo.push_front(d3);
                                  }
                                  if( recta[i+1][j].getEdo() == 3 || recta[i+1][j].getEdo() == 5 || recta[i+1][j].getEdo() == 6 )
                                  {
                                       tempo.push_front(d4);
                                  }

                                  int peq =  *std::min_element(tempo.constBegin(), tempo.constEnd());

                                      if( d1 == peq && ( NewmanOffset(i,j,3,1) || NewmanOffset(i,j,5,1) || NewmanOffset(i,j,6,1) ))
                                      {
                                          min[i][j] = 1;
                                          aux[i][j] = 5;
                                      }
                                      else if( d2 == peq && ( NewmanOffset(i,j,3,2) || NewmanOffset(i,j,5,2) || NewmanOffset(i,j,6,2) ))
                                      {
                                          min[i][j] = 2;
                                          aux[i][j] = 5;
                                      }
                                      else if(  d3 == peq && ( NewmanOffset(i,j,3,3) || NewmanOffset(i,j,5,3) || NewmanOffset(i,j,6,3) ))
                                      {
                                          min[i][j] = 3;
                                          aux[i][j] = 5;
                                      }
                                      else if  (  d4 == peq  && ( NewmanOffset(i,j,3,4) || NewmanOffset(i,j,5,4) || NewmanOffset(i,j,6,4)  ) )
                                      {
                                          min[i][j] = 4;
                                          aux[i][j] = 5;
                                      }
                            }
                        }
                        else   // "normal exploration"
                        {

                            if(  getNewman(i,j,0) == 0 && getNewman(i,j,7) == 0)
                            {                                
                                  int d1 = val[i][j+1];
                                  int d2 = val[i-1][j];
                                  int d3 = val[i][j-1];
                                  int d4 = val[i+1][j];

                                  QVector<int> tempo;

                                  if( recta[i][j+1].getEdo() == 3 || recta[i][j+1].getEdo() == 5 || recta[i][j+1].getEdo() == 6 )
                                  {
                                      tempo.push_front(d1);
                                  }
                                  if( recta[i-1][j].getEdo() == 3 || recta[i-1][j].getEdo() == 5 || recta[i-1][j].getEdo() == 6 )
                                  {
                                       tempo.push_front(d2);
                                  }
                                  if( recta[i][j-1].getEdo() == 3 || recta[i][j-1].getEdo() == 5 || recta[i][j-1].getEdo() == 6 )
                                  {
                                       tempo.push_front(d3);
                                  }
                                  if( recta[i+1][j].getEdo() == 3 || recta[i+1][j].getEdo() == 5 || recta[i+1][j].getEdo() == 6 )
                                  {
                                       tempo.push_front(d4);
                                  }

                                  int peq =  *std::min_element(tempo.constBegin(), tempo.constEnd());

                                      if( d1 == peq && ( NewmanOffset(i,j,3,1) || NewmanOffset(i,j,5,1) || NewmanOffset(i,j,6,1) ))
                                      {
                                          min[i][j] = 1;
                                          aux[i][j] = 5;
                                      }
                                      else if( d2 == peq && ( NewmanOffset(i,j,3,2) || NewmanOffset(i,j,5,2) || NewmanOffset(i,j,6,2) ))
                                      {
                                          min[i][j] = 2;
                                          aux[i][j] = 5;
                                      }
                                      else if(  d3 == peq && ( NewmanOffset(i,j,3,3) || NewmanOffset(i,j,5,3) || NewmanOffset(i,j,6,3) ))
                                      {
                                          min[i][j] = 3;
                                          aux[i][j] = 5;
                                      }
                                      else if  (  d4 == peq  && ( NewmanOffset(i,j,3,4) || NewmanOffset(i,j,5,4) || NewmanOffset(i,j,6,4)  ) )
                                      {
                                          min[i][j] = 4;
                                          aux[i][j] = 5;
                                      }
                            }
                         }
                        stateExplore++;
                break;
                case 5:  // gel with nutrients

                        if( !dep(i,j,8) && !dep(i,j,5) && getNewman(i,j,6) == 0 && getNewman(i,j,4) == 0 && getNewman(i,j,1) == 0 && getNewman(i,j,3) == 0 )
                        {
                              aux[i][j] = 0;
                              min[i][j] = 0;
                        }                      
                        else
                        {
                             aux[i][j] = 8;
                        }

                        stateActive++;
                break;

                case 7: // physarum expansion
                    if( getNewman(i,j,5) > 0 || getNewman(i,j,6) > 0 || getNewman(i,j,3) > 0|| getNewman(i,j,4) > 0 )
                    {
                        aux[i][j] = 4;
                    }
                    stateExpand++;
                break;

                case 8:  // gel without nutrients
                    aux[i][j] = 5;
                        stateSemiActive++;
                break;
            }
        }

    }

    newGeneration();


    x.push_front( incre );
    y.push_front( stateActive );
    y2.push_front( stateNutrient );
    y3.push_front( stateExplore );
    y4.push_front( stateSpace );
    y5.push_front( stateSemiActive );
    y6.push_front( stateExpand );

    if( stateNutrient > stateActive && stateNutrient > stateExplore && stateNutrient > stateSemiActive && stateNutrient > mayor )
    {
        mayor = stateNutrient;
    }
    else if( stateSemiActive > stateActive && stateSemiActive >stateExplore && stateSemiActive > mayor )
    {
        mayor = stateSemiActive;
    }
    else if( stateActive >stateExplore && stateActive > mayor )
    {
        mayor = stateActive;
    }
    else if(  stateExplore > mayor )
    {
        mayor = stateExplore;
    }

    ui->generationLabel->setText( "  T =  " + QString::number(incre)
                                            + " - Q<sub>1</sub> = " + QString::number(stateNutrient)
                                            + " - Q<sub>4</sub> = " + QString::number(stateExplore)
                                            + " - Q<sub>5</sub> = " + QString::number(stateActive)
                                            + " - Q<sub>7</sub> = " + QString::number(stateExpand)
                                            + " - Q<sub>8</sub> = " + QString::number(stateSemiActive)
                                  );

    updateGraphic();
}

void MainWindow::updateDimension()
{


    rastre->stop();
    timer->stop();



    scene = new QGraphicsScene(this);        
    scene->installEventFilter(this);

    ui->graphicsView->setScene(scene);    

    ui->checkHormiga->setChecked(false);
    int ancho = ui->graphicsView->width();
    ///////////
    dm = ( ancho ) / dimension;

    /////////////

    recta = new Rectangulo*[dimension];   
    aux = new int*[dimension];    
    min = new int*[dimension];
    val = new int*[dimension];

    incre = 0;
    stateActive = 0;
    stateNutrient = 0;
    stateExplore = 0;
    stateSpace = 0;
    stateSemiActive = 0;
    stateExpand = 0;

    mayor = 0;
    x.clear();
    y.clear();
    y2.clear();
    y3.clear();
    y4.clear();
    y5.clear();
    y6.clear();




    for(int i = 0; i < dimension; i++)
    {
        recta[i] = new Rectangulo[dimension];

        aux[i] = new int[dimension];        

        min[i] = new int[dimension];

        val[i] = new int[dimension];

        for(int j = 0; j < dimension; j++)
        {
         recta[i][j].setAttrib(j*dm,i*dm,dm);

         min[i][j] = 0;

         val[i][j] = 0;

         if( i == 0 || i == dimension-1 || j == 0 || j == dimension -1 )
         {
             recta[i][j].setEdo(2);
         }

        }
    }

    for(int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
            scene->addItem(&recta[i][j]);
        }
    }

    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);    
    ui->LabelDim->setText( "Actual dimension: " + QString::number( dimension ) );

    //delete socket;
    //socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);


    ui->generationLabel->setText( "  T =  " + QString::number(0)
                                            + " - Q<sub>1</sub> = " + QString::number(0)
                                            + " - Q<sub>4</sub> = " + QString::number(0)
                                            + " - Q<sub>5</sub> = " + QString::number(0)
                                            + " - Q<sub>7</sub> = " + QString::number(0)
                                            + " - Q<sub>8</sub> = " + QString::number(0)
                                  );

    Caso = false;
    QPixmap pixmap("off.png");
    QIcon ButtonIcon(pixmap);
    //ui->Comportamiento->setIcon(ButtonIcon);


}

void MainWindow::actualiza(int i, int j,int orientacion)
{
    switch( orientacion )
        {
            case 1:
                    if( recta[i][j+1].getEdo() == 4 || recta[i][j+1].getEdo() == 3 || recta[i][j+1].getEdo() == 6)
                    {
                        aux[i][j] = 7;
                    }
                break;
            case 2:
                    if( recta[i-1][j].getEdo() == 4 || recta[i-1][j].getEdo() == 3 || recta[i-1][j].getEdo() == 6)
                    {
                        aux[i][j] = 7;
                    }
                break;
            case 3:
                    if( recta[i][j-1].getEdo() == 4 || recta[i][j-1].getEdo() == 3  || recta[i][j-1].getEdo() == 6)
                    {
                        aux[i][j] = 7;
                    }
                break;
            case 4:
                    if( recta[i+1][j].getEdo() == 4 || recta[i+1][j].getEdo() == 3  || recta[i+1][j].getEdo() == 6)
                    {
                        aux[i][j] = 7;
                    }
                break;
        }

}

void MainWindow::newGeneration()
{
    for(int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
         recta[i][j].setEdo( aux[i][j] );
         recta[i][j].update();
        }
        //qDebug() << "***";
    }


}


int MainWindow::getNewman(int i, int j, int crit)
{
    int x = 0;


    if( recta[i][j+1].getEdo() == crit ) {  x++;  }
    if( recta[i-1][j].getEdo() == crit ) {  x++;  }
    if( recta[i][j-1].getEdo() == crit ) {  x++;  }
    if( recta[i+1][j].getEdo() == crit ) {  x++;  }



    return x;

}

bool MainWindow::NewmanOffset(int i, int j, int crit, int orien)
{


   if( recta[i][j+1].getEdo() == crit && orien == 1)
   {
       return true;
   }
   else
   if( recta[i-1][j].getEdo() == crit && orien == 2)
   {
       return true;
   }
   else
   if( recta[i][j-1].getEdo() == crit && orien == 3 )
   {
       return true;
   }
   else
   if( recta[i+1][j].getEdo() == crit && orien == 4)
   {
       return true;
   }
   return false;
}

bool MainWindow::dep(int i, int j, int crit)
{
    if( recta[i][j+1].getEdo() == crit && min[i][j+1] == 3 )
    {
        return true;
    }
    else
    if( recta[i-1][j].getEdo() == crit && min[i-1][j] == 4 )
    {
        return true;
    }
    else
    if( recta[i][j-1].getEdo() == crit && min[i][j-1] == 1 )
    {
        return true;
    }
    else
    if( recta[i+1][j].getEdo() == crit && min[i+1][j] == 2 )
    {
        return true;
    }
    return false;
}


int MainWindow::random()
{
    return qrand() % ((100 + 1) - 0) + 0;
}

int MainWindow::randomOffset()
{
    return qrand() % ((3 + 1) - 0) + 0;
}

void MainWindow::on_StartButton_clicked()
{
    //generations = number;
    timer->start();
    //evaluar();
}

void MainWindow::on_StopButton_clicked()
{
    timer->stop();
}

void MainWindow::on_colorButton_clicked()
{

    QString edo = ui->stateBox->currentText();

    int valor;

    if( QString::compare("Free space",edo,Qt::CaseInsensitive)  == 0 )
    {
        valor = 0;
    }
    else
    if( QString::compare("Source",edo,Qt::CaseInsensitive)  == 0 )
    {
        valor = 1;
    }
    else
    if( QString::compare("Repellent",edo,Qt::CaseInsensitive)  == 0 )
    {
        valor = 2;
    }
    else
    if( QString::compare("Initial point",edo,Qt::CaseInsensitive)  == 0 )
    {
        valor = 3;
    }


    for(int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
            recta[i][j].setBrocha( valor );
        }
    }


}

void MainWindow::on_dimButton_clicked()
{
    timer->stop();
    dimension = ui->dimensionText->text().toInt();
    updateDimension();
}

void MainWindow::on_fileButton_clicked()
{

      int newDim = 0;
      int i = 0;
      bool llave = false;

      QString fileName1 = QFileDialog::getOpenFileName(this,tr("Open Text File"), "", tr("Text Files (*.txt)"));

      QFile inputFile(fileName1);
      if (inputFile.open(QIODevice::ReadOnly))
      {
         QTextStream in(&inputFile);
         while (!in.atEnd())
         {

            QString line = in.readLine();
            newDim = line.size();

            if( newDim != 0 )
             {
                if(!llave)
                {

                    llave = true;
                    dimension = newDim;
                    updateDimension();
                }


                for(int j = 0; j < dimension; j++)
                {
                     char chara = line.at(j).toLatin1();
                     aux[i][j] = (int) chara - 48;
                }
                i++;
             }
         }
         inputFile.close();
      }

      newGeneration();

}

void MainWindow::on_salvaButton_clicked()
{
    QString filename= QFileDialog::getSaveFileName( ) + ".txt";

    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        QString cadena = "";


        for(int i = 0; i < dimension; i++)
        {
            for(int j = 0; j < dimension; j++)
            {
                cadena = cadena + QString::number( recta[i][j].getEdo() );
            }

            cadena = cadena + "\n";
            stream << cadena;
            cadena = "";
        }

    }

    file.close();
}

void MainWindow::updateGraphic()
{
    // create graph and assign data to it:
    ui->graphicWidget->addGraph();
    ui->graphicWidget->graph(0)->setPen(QColor(0,153,0,255));
    ui->graphicWidget->graph(0)->setData(x, y);
    ui->graphicWidget->addGraph();
    ui->graphicWidget->graph(1)->setPen(QColor(255,230,0, 255));
    ui->graphicWidget->graph(1)->setData(x, y3);
    ui->graphicWidget->addGraph();
    ui->graphicWidget->graph(2)->setPen(QColor(64,185,64,255));
    ui->graphicWidget->graph(2)->setData(x, y5);
    ui->graphicWidget->addGraph();
    ui->graphicWidget->graph(3)->setPen(QColor(160,128,128,255));
    ui->graphicWidget->graph(3)->setData(x, y6);
    ui->graphicWidget->addGraph();
    //ui->graphicWidget->graph(4)->setPen(QColor(0, 0, 204, 255));
    ui->graphicWidget->graph(4)->setData(x, y2);
    // give the axes some labels:
    ui->graphicWidget->xAxis->setLabel("Generation");
    ui->graphicWidget->yAxis->setLabel("Cells");
    // set axes ranges, so we see all data:
    ui->graphicWidget->xAxis->setRange(0, incre );
    ui->graphicWidget->yAxis->setRange(0, mayor );
    ui->graphicWidget->replot();
}





void MainWindow::on_OffB_clicked()
{
   rastre->stop();
   socket->write("0");

}

void MainWindow::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
    qDebug() << "Found new device:" << device.name() << '(' << device.address().toString() << ')';

    ui->ListaV->addItem(  device.address().toString() );
}

void MainWindow::on_ListaV_itemClicked(QListWidgetItem *item)
{
    string = item->text();

    ui->ListaV->addItem(string);

    socket->connectToService(QBluetoothAddress(string), QBluetoothUuid::SerialPort, QIODevice::ReadWrite);

    qDebug() << "--> " << socket->errorString();

}



void MainWindow::timerGeneral(int a)
{
    timer->setInterval(a);
}


void MainWindow::Cambio()
{

    QPixmap pixmap("off.png"),pixmap2("on.png");
    qDebug() << Caso;


    Caso = !Caso;

    if( Caso )
    {
        QIcon ButtonIcon(pixmap2);
        ui->Comportamiento->setIcon(ButtonIcon);
    }
    else
    {        
        QIcon ButtonIcon(pixmap);
        ui->Comportamiento->setIcon(ButtonIcon);
    }


}


bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    int xP;
    int yP;

    //qDebug() << "--> Dim " << dm;

    if ( target == scene && ui->checkHormiga->isChecked() )
    {
        if( event->type() == QEvent::GraphicsSceneMousePress )
        {
            delete hormiga;
            hormiga = new Hormiga();
            const QGraphicsSceneMouseEvent* const me = static_cast <const QGraphicsSceneMouseEvent*>(event);
            const QPointF position = me->scenePos();
            //qDebug() << position.x() << " : "  << position.y();
            xP = position.x();
            yP = position.y();

            for(int i = 0; i < dimension; i++)
            {
                for( int j = 0; j < dimension; j++ )
                {

                    if( (j*dm) < xP && (i*dm) < yP && ((j+1)*dm) > xP && ((i+1)*dm) > yP )
                    {
                        hormiga->setAttrib(j*dm,i*dm,dm);
                        hormiga->setCoord(i,j);
                        hormiga->setFrente(1);
                        scene->addItem( hormiga );
                        break;
                    }

                }
            }


        }
    }

    return QMainWindow::eventFilter(target,event);

}



void MainWindow::on_checkHormiga_clicked()
{

    //hormiga = new Hormiga();
    //scene->addItem(hormiga);

    for(int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
            recta[i][j].setLlave();
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    rastre->start();
    //rastreo();
}

void MainWindow::rastreo()
{
        int posX = hormiga->getX();
    int posY = hormiga->getY();

    //qDebug() << "-->Frente: " << hormiga->getFrente();


    switch(hormiga->getFrente())
    {
        case 1:



            if( recta[posY-1][posX].getEdo() == 3 || recta[posY-1][posX].getEdo() == 5 || recta[posY-1][posX].getEdo() == 6 || recta[posY-1][posX].getEdo() == 8 )
            {


                delete hormiga;
                hormiga = new Hormiga();

                hormiga->setAttrib(posX*dm,(posY-1)*dm,dm);
                hormiga->setCoord(posY-1,posX);
                hormiga->setFrente(2);

                scene->addItem(hormiga);

                socket->write("1");
                socket->write("3");

            }
            else
            {

                if( recta[posY][posX+1].getEdo() == 3 || recta[posY][posX+1].getEdo() == 5 || recta[posY][posX+1].getEdo() == 6 || recta[posY][posX+1].getEdo() == 8 )
                {

                    delete hormiga;
                    hormiga = new Hormiga();

                    hormiga->setAttrib((posX+1)*dm,posY*dm,dm);
                    hormiga->setCoord(posY,posX+1);

                    scene->addItem(hormiga);

                    socket->write("3");

                }
                else
                {
                    //qDebug() << "--> Entre en Cambio";
                    hormiga->setFrente(4);

                    socket->write("2");

                }
            }


        break;

        case 2:



            if( recta[posY][posX-1].getEdo() == 3 || recta[posY][posX-1].getEdo() == 5 || recta[posY][posX-1].getEdo() == 6 || recta[posY][posX-1].getEdo() == 8 )
            {

                delete hormiga;
                hormiga = new Hormiga();

                hormiga->setAttrib((posX-1)*dm,posY*dm,dm);
                hormiga->setCoord(posY,posX-1);
                hormiga->setFrente(3);

                scene->addItem(hormiga);

                socket->write("1");
                socket->write("3");

            }
            else
            {

                if( recta[posY-1][posX].getEdo() == 3 || recta[posY-1][posX].getEdo() == 5 || recta[posY-1][posX].getEdo() == 6 || recta[posY-1][posX].getEdo() == 8 )
                {
                    delete hormiga;
                    hormiga = new Hormiga();

                    hormiga->setAttrib(posX*dm,(posY-1)*dm,dm);
                    hormiga->setCoord(posY-1,posX);

                    scene->addItem(hormiga);

                    socket->write("3");

                }
                else
                {
                    hormiga->setFrente(1);

                    socket->write("2");
                }
            }
        break;

        case 3:

            if( recta[posY+1][posX].getEdo() == 3 || recta[posY+1][posX].getEdo() == 5 || recta[posY+1][posX].getEdo() == 6 || recta[posY+1][posX].getEdo() == 8 )
            {

                delete hormiga;
                hormiga = new Hormiga();

                hormiga->setAttrib(posX*dm,(posY+1)*dm,dm);
                hormiga->setCoord(posY+1,posX);
                hormiga->setFrente(4);

                scene->addItem(hormiga);

                socket->write("1");
                socket->write("3");

            }
            else
            {

                if( recta[posY][posX-1].getEdo() == 3 || recta[posY][posX-1].getEdo() == 5 || recta[posY][posX-1].getEdo() == 6 || recta[posY][posX-1].getEdo() == 8 )
                {
                    delete hormiga;
                    hormiga = new Hormiga();

                    hormiga->setAttrib((posX-1)*dm,posY*dm,dm);
                    hormiga->setCoord(posY,posX-1);

                    scene->addItem(hormiga);

                    socket->write("3");

                }
                else
                {
                    hormiga->setFrente(2);

                    socket->write("2");
                }
            }
        break;

        case 4:

            if( recta[posY][posX+1].getEdo() == 3 || recta[posY][posX+1].getEdo() == 5 || recta[posY][posX+1].getEdo() == 6 || recta[posY][posX+1].getEdo() == 8 )
            {

                delete hormiga;
                hormiga = new Hormiga();

                hormiga->setAttrib((posX+1)*dm,posY*dm,dm);
                hormiga->setCoord(posY,posX+1);
                hormiga->setFrente(1);

                scene->addItem(hormiga);

                socket->write("1");
                socket->write("3");

            }
            else
            {

                if( recta[posY+1][posX].getEdo() == 3 || recta[posY+1][posX].getEdo() == 5 || recta[posY+1][posX].getEdo() == 6 || recta[posY+1][posX].getEdo() == 8 )
                {
                    delete hormiga;
                    hormiga = new Hormiga();

                    hormiga->setAttrib(posX*dm,(posY+1)*dm,dm);
                    hormiga->setCoord(posY+1,posX);
                    scene->addItem(hormiga);

                    socket->write("3");

                }
                else
                {
                    hormiga->setFrente(3);

                    socket->write("2");
                }
            }
        break;
    }

}


void MainWindow::on_AcercaB_clicked()
{
    nuevoD = new Dialog(this);
    nuevoD->show();
}


void MainWindow::on_vola_clicked()
{
    double factor = 1.5;
    ui->graphicsView->scale(factor,factor);
    }

void MainWindow::on_volb_clicked()
{
    double factor = 1.5;
    ui->graphicsView->scale(1/factor,1/factor);
}

void MainWindow::on_pushButton_2_clicked()
{

    cuadN = new Cuadro(this);

    QString edo = ui->statesGraph->currentText();


    if( QString::compare("Free Space",edo,Qt::CaseInsensitive)  == 0 )
    {
       cuadN->setArreglo(y4,x);
    }
    else
    if( QString::compare("Sources",edo,Qt::CaseInsensitive)  == 0 )
    {
       cuadN->setArreglo(y2,x);
    }
    else
    if( QString::compare("Physarum expansion",edo,Qt::CaseInsensitive)  == 0 )
    {
       cuadN->setArreglo(y6,x);
    }
    else
    if( QString::compare("Gel in evaluation",edo,Qt::CaseInsensitive)  == 0 )
    {
       cuadN->setArreglo(y3,x);
    }
    else
    if( QString::compare("Gel with nutrients",edo,Qt::CaseInsensitive)  == 0 )
    {
       cuadN->setArreglo(y,x);
    }
    else
    if( QString::compare("Gel without nutrients",edo,Qt::CaseInsensitive)  == 0 )
    {
       cuadN->setArreglo(y5,x);
    }


    cuadN->show();

}



void MainWindow::on_Comportamiento_clicked()
{
    Cambio();
    qDebug() << "sdasd";
}
