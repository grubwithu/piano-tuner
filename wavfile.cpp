#include "wavfile.h"

WAVFILE::WAVFILE(QString fileName)
{
    fileLength = 0;
    QFile fileInfo(fileName);
    if(!fileInfo.open(QIODevice::ReadOnly)) return;
    riffName = fileInfo.read(4);
    fileLength+=4;
    fileInfo.read((char*)(&afterRiffLength),4);
    fileLength+=4;
    wavName = fileInfo.read(4);
    fileLength+=4;
    fmtName = fileInfo.read(4);
    fileLength+=4;
    fileInfo.read((char*)(&afterFmtLength),4);
    fileLength+=4;
    fileInfo.read((char*)(&audioFormat),2);
    fileLength+=2;
    fileInfo.read((char*)(&channleNumber),2);
    fileLength+=2;
    fileInfo.read((char*)(&sampleRate),4);
    fileLength+=4;
    fileInfo.read((char*)(&bytesPerSecond),4);
    fileLength+=4;
    fileInfo.read((char*)(&bytesPerSample),2);
    fileLength+=2;
    fileInfo.read((char*)(&bitsPerSample),2);
    fileLength+=2;
    if(afterFmtLength>=18)
    {
        fileInfo.read((char*)(&appendMessage),2);
        fileLength+=2;
        if(appendMessage>0)
            appendMessageData = fileInfo.read(appendMessage);
        fileLength+=appendMessage;
    }
    factName = fileInfo.peek(4);
    QByteArray temp("fact");
    if(factName==temp)
    {
        fileInfo.read(4);
        fileLength+=4;
        fileInfo.read((char*)(&afterFactLength),4);
        fileLength+=4;
        factData = fileInfo.read(afterFactLength);
        fileLength+=afterFactLength;
    }
    dataName = fileInfo.read(4);
    fileLength+=4;
    fileInfo.read((char*)(&afterDataLength),4);
    fileLength+=4;

    pcmData = fileInfo.readAll();
    fileLength+=pcmData.size();
}

int WAVFILE::getPcmLength()
{
    return pcmData.length();
}

int WAVFILE::getFullLength()
{
    return fileLength;
}

QByteArray WAVFILE::getPcmData()
{
    return pcmData;
}

int WAVFILE::getSampleRate()
{
    return static_cast<int>(sampleRate);
}

int WAVFILE::getChannelNumber()
{
    return static_cast<int>(channleNumber);
}

int WAVFILE::getBitsWidth()
{
    return static_cast<int>(bitsPerSample);
}
