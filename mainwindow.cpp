#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "complexnum.h"
#include "wavfile.h"
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QList>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chart = new QChart();
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->hide();

    chartView = new QChartView(this);
    chartView->show();
    chartView->setGeometry(30,60,631,331);
    chartView->setChart(chart);
    series = new QLineSeries();
    chart->addSeries(series);
    chart->addSeries(series);

    audioRecorder = new QAudioRecorder;
    QAudioEncoderSettings settins;
    settins.setQuality(QMultimedia::LowQuality);
    audioRecorder->setAudioSettings(settins);
    QStringList inputs = audioRecorder->audioInputs();
    ui->comboBox->addItems(inputs);
    audioRecorder->setOutputLocation(QUrl::fromLocalFile("D:/temp"));

    key.initialize("A1");//默认选择A1键
    ui->pianokey->addItems(PianoKey::getPianoKeySequence());

    connect(audioRecorder,&QAudioRecorder::durationChanged,this,[&](qint64 duration){
        if(duration>500)
        {
            audioRecorder->stop();
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_beginButton_clicked()
{
    audioRecorder->record();
}

void MainWindow::on_analyseButton_clicked()
{
    WAVFILE wave("D:/temp.wav");
    QByteArray pcmdata = wave.getPcmData();
    qDebug()<<wave.getSampleRate();
    QList<ComplexNum> source;
    series->clear();
    int sampleLength = 18384 - 2000;
    const double pi = acos(-1);
    for(int i=2000;i<18384;i++)
    {
        source.push_back(ComplexNum(pcmdata[i],0)
                         *(0.5-0.5*(cos(2*pi*(i-2000)/sampleLength))));
    }
    QList<ComplexNum> answer;
    qDebug()<<wave.getPcmLength();
    answer = FFT(source);
    double max = 0;
    double maxID = 0;
    QList<double> range = key.zoneFrequenceRange();//给出频率显示范围
    double from = range[0]*sampleLength/22050;
    double to = range[1]*sampleLength/22050;
    for(int i=static_cast<int>(from);i<to;i++)
    {
        series->append(static_cast<double>(i)*22050/sampleLength,answer[i].getMagnitude());
        if(max<=answer[i].getMagnitude())
        {
            max = answer[i].getMagnitude();
            maxID = static_cast<double>(i)*22050/sampleLength;
        }
    }
    if(max>30000)//判断声音是否过小
    {
        if(abs(key.getFrequence()-maxID)<=5)//判断音准
            ui->frequence->setText(QString("Frequence:%1Hz. %2 is on good inotation!").arg(maxID).arg(key.getName()));
        else
            ui->frequence->setText(QString("Frequence:%1Hz. %2 Key need tuning!").arg(maxID).arg(key.getName()));
    }
    else
    {
        ui->frequence->setText("Sound is too weak.Please record again.");
    }
    chart->removeSeries(series);
    chart->addSeries(series);
    chart->createDefaultAxes();
}

void MainWindow::on_comboBox_currentIndexChanged(QString index)
{
   audioRecorder->setAudioInput(index);
}

void MainWindow::on_pianokey_currentIndexChanged(QString index)
{
    key.initialize(index);
    qDebug()<<key.getName();
}
