#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pianokey.h"
#include <QMainWindow>
#include <QAudioRecorder>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
using namespace QtCharts;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QAudioRecorder *audioRecorder;
    bool selectedDevices = false;
    QLineSeries *series;
    QChart *chart;
    QChartView *chartView;
    PianoKey key;
private slots:
    void on_beginButton_clicked();
    void on_analyseButton_clicked();
    void on_comboBox_currentIndexChanged(QString index);
    void on_pianokey_currentIndexChanged(QString index);

};


#endif // MAINWINDOW_H
