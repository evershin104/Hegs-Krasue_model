#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "calculates.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /* Before graph initialization and entering data */
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_agNumber_textChanged(const QString &arg1)
{
    if (arg1.toInt() < 20 || arg1.toInt() > 500)
    {
        ui->agNumber->setStyleSheet("color: red");
        ui->statusbar->showMessage("Enter the integer number between 20 and 500");
        goodNum = false;
    }
    else {
         ui->agNumber->setStyleSheet("color: black");
         goodNum = true;
         numbOfAg = arg1.toInt();
    }
}

void MainWindow::on_confLevel_textChanged(const QString &arg1)
{
    if (arg1.toDouble() <= 0 || arg1.toDouble() >= 1)
    {
        ui->confLevel->setStyleSheet("color: red");
        ui->statusbar->showMessage("Enter the number between 0 and 1");
        goodConf = false;
    }
    else {
        ui->confLevel->setStyleSheet("color: black");
        goodConf = true;
    }
//    qDebug() << "conf " << ui->confLevel->text().toDouble();
}

void MainWindow::on_error_textChanged(const QString &arg1)
{
    if (arg1.toDouble() <= 0 || arg1.toDouble() >= 1)
    {
        ui->error->setStyleSheet("color: red");
        ui->statusbar->showMessage("Enter the number between 0 and 1");
        goodError = false;
    }
    else {
        ui->error->setStyleSheet("color: black");
        goodError = true;
    }
//    qDebug() << "error " << ui->error->text().toDouble();
}

void MainWindow::on_pushButton_clicked()
{
    if (goodNum && goodConf && goodError) {
        opinions.clear();
        calculates obj;
        obj.takeN(numbOfAg);
        obj.takeEps(ui->confLevel->text().toDouble());
        obj.takeErr(ui->error->text().toDouble());
        obj.initModel();
        ui->data->setPlainText(obj.DataToSet());
        ui->timeLabel->setText(" T = 0");
        opinions = obj.returnOpinions();
        obj.cleanEvol();
        makeChart(0);
        ui->slider->setMinimum(0);
        ui->slider->setMaximum(obj.returnCons());
        ui->slider->setSingleStep(1);
        ui->slider->setValue(0);
    }
}

void MainWindow::makeChart(int t) // Получает время
{
QVector<double> y =  opinions[t];
    QVector<double> x = fillX();

    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->xAxis->setRange(1, numbOfAg);
    ui->customPlot->yAxis->setRange(0, 1);
    ui->customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("ID");
    ui->customPlot->yAxis->setLabel("Opinion");
    ui->customPlot->graph(0)->setPen(QPen(Qt::red));
    // set axes ranges, so we see all data:
    ui->customPlot->replot();
}


void MainWindow::on_slider_sliderMoved(int position)
{
    ui->customPlot->clearGraphs();
    makeChart(position);
    ui->timeLabel->setText(" T = " + QString::number(position));
}


