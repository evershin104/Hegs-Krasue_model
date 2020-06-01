#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    bool goodNum, goodConf, goodError;                  // If entered data correct => true
    int numbOfAg;                                                      // Number of agents
    /* Fills Ox dataset from 1 to number if agents, rougly speaking it's their IDs */
    QVector<double> fillX(void) {
        QVector<double> toRet;
        for (int i = 1; i <= numbOfAg; i++ ) { toRet.push_back(i); }
        return toRet;
    }
    QVector<QVector<double>> opinions;                  //Opinions of agents for each time

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:


private slots:
    void on_agNumber_textChanged(const QString &arg1);          // Processes entered data

    void on_confLevel_textChanged(const QString &arg1);           // Processes entered data

    void on_error_textChanged(const QString &arg1);                  // Processes entered data

    void on_pushButton_clicked();                                                 // Inits model when data is correct

    void makeChart(int t);                                                              // Makeschart for time = t

    void on_slider_sliderMoved(int position);                               //  Remake chart for t = position


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
