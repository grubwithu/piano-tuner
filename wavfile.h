#ifndef WAVFILE_H
#define WAVFILE_H

#include <QByteArray>
#include <QFile>

class WAVFILE
{
public:
    WAVFILE(QString fileName);
    int getFullLength();//获取文件总长度
    int getPcmLength();//获取音频数据总程度
    int getSampleRate();//获取采样率
    int getChannelNumber();//获取通道数
    int getBitsWidth();//获取每个样本的位数
    QByteArray getPcmData();//获取音频数据
private:
    int fileLength;
    //RIFF 头
    QByteArray riffName;
    unsigned long afterRiffLength;
    //数据类型标识符
    QByteArray wavName;
    //格式块
    QByteArray fmtName;
    unsigned long afterFmtLength;
    unsigned short audioFormat;
    unsigned short channleNumber;
    unsigned long sampleRate;
    unsigned long bytesPerSecond;
    unsigned short bytesPerSample;
    unsigned short bitsPerSample;
    //扩展域
    unsigned short appendMessage;
    QByteArray appendMessageData;
    //Fact 块
    QByteArray factName;
    unsigned long afterFactLength;
    QByteArray factData;
    //数据块
    QByteArray dataName;
    unsigned long afterDataLength;

    QByteArray pcmData;
};

#endif // WAVFILE_H
