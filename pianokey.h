#ifndef PIANOKEY_H
#define PIANOKEY_H

#include <QList>

class PianoKey
{
public:
    PianoKey(){}
    PianoKey(QString name);
    static QStringList getPianoKeySequence();
    void initialize(QString name);
    double getFrequence();
    QList<double> zoneFrequenceRange();
    QString getName();
private:
    inline static QList<double> basicFrequence
    {0,27.5,29.135,30.868,32.703,34.648,36.708,38.891,41.203,43.654,46.249,48.999,51.913};
    inline static QStringList noteName
    {"","A","#A","B","C","#C","D","#D","E","F","#F","G","#G"};

    int serialNumber=1;
    int zoneNumber=1;
    double frequence=27.5;
};

//QList<double> initial_Frequence();
//QList<double> PianoKey::basicFrequence(initial_Frequence());

//QStringList initial_Name();
//QStringList PianoKey::noteName(initial_Name());
#endif // PIANOKEY_H
