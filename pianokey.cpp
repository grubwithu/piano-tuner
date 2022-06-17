#include "pianokey.h"

PianoKey::PianoKey(QString name)
{
    initialize(name);
}

QStringList PianoKey::getPianoKeySequence()
{
    int full = 0;
    QStringList ans;
    for(int zone=1;zone<=8;zone++)
    {
        for(int serial=1;serial<=12;serial++)
        {
            if(serial<=3)
                ans.push_back(QString(noteName[serial])+QString::number(zone-1));
            else
                ans.push_back(QString(noteName[serial])+QString::number(zone));
            full++;
            if(full==88)
                return ans;
        }
    }
    return ans;
}

void PianoKey::initialize(QString name)
{
    if(name[0]=='#')
    {
        for(serialNumber=1;serialNumber<=12;serialNumber++)
        {
            if(noteName[serialNumber][0]==name[1])
            {
                serialNumber++;
                break;
            }
        }
        name[0]='0';
        name[1]='0';
        zoneNumber = name.toInt();
        if(serialNumber<=3)zoneNumber++;
    }
    else
    {
        for(serialNumber=1;serialNumber<=12;serialNumber++)
        {
            if(noteName[serialNumber][0]==name[0])
            {
                break;
            }
        }
        name[0]='0';
        zoneNumber = name.toInt();
        if(serialNumber<=3)zoneNumber++;
    }
    frequence = pow(2,zoneNumber-1) * basicFrequence[serialNumber];
}

double PianoKey::getFrequence()
{
    return frequence;
}

QList<double> PianoKey::zoneFrequenceRange()
{
    QList<double> ans;
    if(frequence<200)
    {
        ans.push_back(0);
        ans.push_back(frequence*2);
    }
    else
    {
        ans.push_back(frequence-200);
        ans.push_back(frequence+200);
    }
    return ans;
}

QString PianoKey::getName()
{
    QString ans;
    ans.push_back(noteName[serialNumber]);
    if(serialNumber<=3)
        ans.push_back(QString::number(zoneNumber-1));
    else
        ans.push_back(QString::number(zoneNumber));
    return ans;
}
