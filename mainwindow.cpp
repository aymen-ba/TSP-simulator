#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"
#include "vertex.h"
#include "edge.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(400,400);
    Scene = new QGraphicsScene(0,0,300,300);
    View = new QGraphicsView(Scene);
    View->scale(qreal(0.9), qreal(0.9));
    Timer = new QTimer(this);
    connect(Timer, SIGNAL(timeout()),this, SLOT(myTimer()));
    Timer->start(0);
    ui->statusBar->showMessage("Drag and drop any node and use zoom with scrollbar",0);
    graph  = NULL;
    solutionGraph = NULL;
    createInterface();

}

MainWindow::~MainWindow()
{
    delete Scene;
    delete View;
    delete Timer;
    if (graph != NULL)
        delete graph;
    delete centralLayout;
    delete ui;
}

void MainWindow::createInterface()
{
    View->setRenderHint(QPainter::Antialiasing);
    View->setMinimumSize(380, 200);
    centralLayout = new QHBoxLayout();
    centralLayout->addWidget(View);
    centralLayout->addStretch();
    ui->viewContentLayout->addLayout(centralLayout);
}

void MainWindow::myTimer()
{
    Scene->update();
}

void MainWindow::on_pushButton_clicked()
{
    Scene->clear();
    if(ui->nVertex->text().toInt()>0)
    {
        graph = new Graph(Scene, ui->nVertex->text().toInt());
        graph->addVertex(Scene);
        graph->allocateEdges();
    }
}

void MainWindow::on_pushButton_2_clicked()
{

    if(graph != NULL)
    {
        solutionGraph = new TSPGraph(graph->getNVertex(),graph->getVector());
        ui->statusBar->showMessage("Costo total del ciclo Hamiltoniano: " + QString::number(solutionGraph->costoCiclo()),0);
        if(graph->getNVertex() > 1)
            graph->drawPath(solutionGraph->recorrido());

        delete solutionGraph;
        solutionGraph = NULL;
    }
}

void MainWindow::on_zoomIn_clicked()
{
    scaleView(qreal(1.2));
}

void MainWindow::on_zoomOut_clicked()
{
    scaleView(1 / qreal(1.2));
}

void MainWindow::scaleView(qreal scaleFactor)
{
    View->scale(scaleFactor, scaleFactor);
}
void MainWindow::on_actionQuit_triggered()
{
    this->close();
}
void MainWindow::on_actionAbout_2_triggered()
{
    QMessageBox About;
    About.setContentsMargins(0,10,20,10);
    About.setWindowTitle("About TSP Solver");
    About.setText("Travelling salesman problem simulation<br/>Framework :<br/>Qt 4.8.5<br/>Qt Creator 2.8.0<br/>GCC 4.8.1<br/>GNU/Linux 3.11.3<br/>Github Repositry:<a href='https://github.com/aymanous/TSP-simulator'>https://github.com/aymanous/TSP</a>");
    About.exec();
}
