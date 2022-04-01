#include "parsegithubdata.h"
#include <QtNetwork>

parsegithubData::parsegithubData()
{

}
QString pathString;
QList<QString> parsegithubData::readTrackData()
{
    //qDebug() <<"readTrackData";
    QList<QPair<QString,QString>> returnData;




    #ifdef __linux__
        pathString = ("/opt/PowerTune/repo.txt"); // Opens the embeded KML file/txt
    #elif _WIN32
        pathString = (QCoreApplication::applicationFilePath().remove("release/PowertuneQMLGui.exe") + "repo.txt"); // Opens the repo track list
    #else

    #endif


    QFile inputFile(pathString);
    //qDebug()<< inputFile.fileName();
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd()) // Reads line and puts it in a string + Debug output of the string
        {
            QPair<QString,QString> tempPair;
            QString line = in.readLine();
            //qDebug() << line;
            QList<QString> splitList = line.split(":");
            tempPair.first = splitList[0];
            tempPair.second = splitList[1];
            returnData.append(tempPair);
        }
        inputFile.flush();
        inputFile.close();
    }

    pairs = returnData;
    QList<QString> returnStringList;
    for(QPair<QString,QString> pair: returnData)
    {
        QString tempString;
        //tempString = "https://raw.githubusercontent.com/Deadelven/PTKML/main/kmls/" + pair.first + "/" +pair.second+".txt";
        tempString = "https://gitlab.com/PowerTuneDigital/PowertuneTracks/-/raw/main/Tracks/" + pair.first + "/" +pair.second;
        returnStringList.append(tempString);
    }
    return returnStringList;
}

void parsegithubData::sortDownloadedFiles()
{
    //qDebug() << "SortFiles";
    QString p2String;
    QString destinationString;

    QDir dir;

    #ifdef __linux__
        p2String = ("/opt/PowerTune/");
        destinationString = ("/home/pi/KTracks/");
    #elif _WIN32
        p2String = pathString.remove("repo.txt");
        destinationString = pathString.remove("repo.txt");
    #else

    #endif




    for(QPair<QString,QString> pair: pairs)
    {
        QFileInfo outputDir(destinationString+pair.first);
       // qDebug() <<"Output directory"<< outputDir;
        QFileInfo outputFile(destinationString+pair.first+"/"+pair.second);
       // qDebug() <<"Output file"<<outputFile;
        if(!outputDir.exists())
        {
           // qDebug() <<"Create Directory";
            dir.mkpath(destinationString+pair.first);
        }

        if(outputFile.exists())
        {
            //qDebug() << "removing !!!! " ;
            dir.remove(destinationString+pair.first+"/"+pair.second);
        }
       // qDebug() << "CopyString " << p2String+pair.second << " TO " << destinationString+pair.first+"/" + pair.second;
        //QFile::copy(p2String+pair.second, destinationString+pair.first+"/" + pair.second);
        if(!QFile::copy(p2String+pair.second, destinationString+pair.first+"/" + pair.second)){
                     // qDebug() << "Copy Failure!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"; // Still need to do something here in case copy fails
              }
        //remove original files after they been copied
        QFile::remove(p2String+pair.second);
    }
}
