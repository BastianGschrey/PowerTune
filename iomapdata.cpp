#include "iomapdata.h"
#include <QtGlobal>



ioMapData::ioMapData(QObject *parent):
QObject(parent)
{
}

QGeoPath ioMapData::loadMapData(QString country, QString trackName)
{
    //Automatically determine the platform Windows or Linux to change the paths
    //    #ifdef __linux__
            QString path ("/home/pi/KTracks/"+ country + "/" + trackName); // Opens the embeded KML file/txt
    //    #elif _WIN32
    //        QString path (":/KTracks/"+ country + "/" + trackName); // Opens the embeded KML file/txt
    //    #else

    //    #endif
    //qDebug() << "LoadKMLData";
    QList<QString> list;
    QList<QString> spl;
    //qDebug() << ("Open KML");
    //Open *.KML/txt file and Serialize the data

    QFile inputFile(path);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        //qDebug() <<"Open successful";
        QTextStream in(&inputFile);
        while (!in.atEnd()) // Reads line and puts it in a string + Debug output of the string
        {
            QString line = in.readLine();
            //qDebug() << line ;
            if(line.contains("KML", Qt::CaseInsensitive))
            {

                spl = line.split(QRegExp ("[:]"));
                spl.removeFirst();
                list = spl[0].split(QRegExp ("[,]"));
                return parseKML(list);

            }

        }
        inputFile.close();

    }
}

QGeoPath ioMapData::parseKML(QList<QString> list)
{
    //qDebug() << "ParseKML";
    QGeoPath path;
    QList<QPair<QString,QString>> locationList;
    QPair<QString,QString> tempStringHold;
    tempStringHold.first = "";
    tempStringHold.second = "";
    for(QString str : list)
    {
        if(str.contains( "0 "))
        {
            //qDebug() << str;
            //qDebug() << "Remove 0 ";
            str.remove("0 ");
            //qDebug() << str;
        }

        if(tempStringHold.first == "")
        {
            tempStringHold.first = str;
        }
        else if( tempStringHold.second == "")
        {
            tempStringHold.second = str;
        }

        if(tempStringHold.first != "" && tempStringHold.second != "")
        {
            locationList.append(tempStringHold);
            tempStringHold.first = "";
            tempStringHold.second = "";

        }

    }

    for( QPair<QString,QString> pair : locationList)
    {
        path.addCoordinate(QGeoCoordinate((pair.second).toFloat(),(pair.first).toFloat()));
    }
    //qDebug() <<"Path returned " << path;

    //engine.rootContext()->setContextProperty("geopath", QVariant::fromValue(path));
    return path;
}

QList<QString> ioMapData::getCountries()
{
    QList<QString> list;
    //Automatically determine the platform Windows or Linux to change the paths
    //   #ifdef __linux__
            QString path ("/home/pi/KTracks/");
    //    #elif _WIN32
    //        QString path (":/KTracks/");
    //    #else

    //    #endif
//////////
    QDir trackfolder = path;

     if (trackfolder.exists()){

             QDirIterator directories(path, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
                 //qDebug() <<"List Directories";
             while(directories.hasNext()){
                 directories.next();
                 QString countrypathname;
                 countrypathname = directories.filePath();
                 //qDebug() << "Full Directory" << countrypathname;
                 countrypathname.remove(0,path.length());
                 //qDebug() << "Directory" << countrypathname;
                 list.append(countrypathname);
             }
 //qDebug() <<"Country count" << list.size();
 }
     else{
     list.append("No Tracks installed");
 }
    return list;
}




QList<QString> ioMapData::getTracks(QString country)
{
    //Automatically determine the platform Windows or Linux to change the paths
       // #ifdef __linux__
            QDir directory("/home/pi/KTracks/"+country+"/");
        //#elif _WIN32
        //    QDir directory(":/KTracks/"+country+"/");
        //#else

        //#endif

   // qDebug() <<"Directory " << directory;
    QStringList trackNames = directory.entryList(QStringList(),QDir::Files);
    foreach(QString filename, trackNames)
    {
        //qDebug()<<filename;
    }
    return trackNames;
}

int ioMapData::getTrackCount(QString country)
{
    //#ifdef __linux__
        QDir directory("/home/pi/KTracks/"+country+"/");
    //#elif _WIN32
      //  QDir directory(":/KTracks/"+country+"/");
    //#else

    //#endif
    qDebug() <<"Directory " << directory;
    QStringList images = directory.entryList(QStringList(),QDir::Files);
    return images.size();
}

int ioMapData::getCountryCount()
{
QList<QString> list;
//Automatically determine the platform Windows or Linux to change the paths
   // #ifdef __linux__
        QString path ("/home/pi/KTracks/");
   // #elif _WIN32
   //     QString path (":/KTracks/");
   // #else

   // #endif

QDir trackfolder = path;

if (trackfolder.exists()){

        QDirIterator directories(path, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
            //qDebug() <<"List Directories";
        while(directories.hasNext()){
            directories.next();
            QString countrypathname;
            countrypathname = directories.filePath();
            //qDebug() << "Full Directory" << countrypathname;
            countrypathname.remove(0,path.length());
            //qDebug() << "Directory" << countrypathname;
            list.append(countrypathname);
        }
}
return list.size();
}

QList<QString> ioMapData::getCenter(QString country, QString trackName)
{
    QList<QString> returnList;
    QList<QString> list;
    QList<QString> spl;
    //Automatically determine the platform Windows or Linux to change the paths
       // #ifdef __linux__
            QString path ("/home/pi/KTracks/"+ country + "/" + trackName); // Opens the embeded KML file/txt
       // #elif _WIN32
       //     QString path (":/KTracks/"+ country + "/" + trackName); // Opens the embeded KML file/txt
       // #else

       // #endif

    //qDebug() << path;
    QFile inputFile(path);
    //qDebug() <<"start Open GetCenter";
    if (inputFile.open(QIODevice::ReadOnly))
    {
        //qDebug() <<"Open successful GetCenter";
        QTextStream in(&inputFile);
        while (!in.atEnd()) // Reads line and puts it in a string + Debug output of the string
        {
            QString line = in.readLine();
            //qDebug() << line ;
            if(line.contains("MAPCENTER", Qt::CaseInsensitive))
            {
                spl = line.split(QRegExp ("[:]"));
                spl.removeFirst();
                list = spl[0].split(QRegExp ("[,]"));

                returnList.append(list[0]);
                returnList.append(list[1]);
               // qDebug()<<"ReturnList";
               // qDebug()<<returnList[0];
               // qDebug()<<returnList[1];

            }

        }
        inputFile.close();
        return returnList;
    }
}

QList<QString> ioMapData::getStartFinishLine(QString country, QString trackName)
{
    QList<QString> list;
    QList<QString> spl;
    QList<QString> floatList;
    //Automatically determine the platform Windows or Linux to change the paths
     //   #ifdef __linux__
            QString path ("/home/pi/KTracks/"+country+"/"+trackName); // Opens the embeded KML file/txt
     //    #elif _WIN32
     //        QString path (":/KTracks/"+country+"/"+trackName); // Opens the embeded KML file/txt
     //    #else

     //    #endif

    QFile inputFile(path);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        //qDebug() <<"Open successful";
        QTextStream in(&inputFile);
        while (!in.atEnd()) // Reads line and puts it in a string + Debug output of the string
        {
            QString line = in.readLine();
           // qDebug() << line ;
            if(line.contains("STARTFINISH1", Qt::CaseInsensitive))
            {
                spl = line.split(QRegExp ("[:]"));
                spl.removeFirst();
                list = spl[0].split(QRegExp ("[,]"));

                floatList.append(list[0]);
                floatList.append(list[1]);
                floatList.append(list[2]);
                floatList.append(list[3]);

            }

        }
        inputFile.close();
        return floatList;
    }
}

QList<QString> ioMapData::getSecondFinishLine(QString country, QString trackName)
{
    QList<QString> list;
    QList<QString> spl;
    QList<QString> floatList;
    //Automatically determine the platform Windows or Linux to change the paths
    //     #ifdef __linux__
            QString path ("/home/pi/KTracks/"+country+"/"+trackName); // Opens the embeded KML file/txt
   //      #elif _WIN32
   //          QString path (":/KTracks/"+country+"/"+trackName); // Opens the embeded KML file/txt
   //      #else

    //     #endif

    QFile inputFile(path);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        //qDebug() <<"Open successful";
        QTextStream in(&inputFile);
        while (!in.atEnd()) // Reads line and puts it in a string + Debug output of the string
        {
            QString line = in.readLine();
            //qDebug() << line ;
            if(line.contains("STARTFINISH2", Qt::CaseInsensitive))
            {
                spl = line.split(QRegExp ("[:]"));
                spl.removeFirst();
                list = spl[0].split(QRegExp ("[,]"));

                floatList.append(list[0]);
                floatList.append(list[1]);
                floatList.append(list[2]);
                floatList.append(list[3]);

            }

        }
        inputFile.close();
        return floatList;
    }
}

qreal ioMapData::getZOOMLEVEL(QString country, QString trackName)
{
    QList<QString> list;
    QList<QString> spl;
    //Automatically determine the platform Windows or Linux to change the paths
     //    #ifdef __linux__
            QString path ("/home/pi/KTracks/"+country+"/"+trackName); // Opens the embeded KML file/txt
     //    #elif _WIN32
     //        QString path (":/KTracks/"+country+"/"+trackName); // Opens the embeded KML file/txt
     //    #else

     //    #endif

    QFile inputFile(path);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        //qDebug() <<"Open successful";
        QTextStream in(&inputFile);
        while (!in.atEnd()) // Reads line and puts it in a string + Debug output of the string
        {
            QString line = in.readLine();
            //qDebug() << line ;
            if(line.contains("ZOOMLEVEL", Qt::CaseInsensitive))
            {
                spl = line.split(QRegExp ("[:]"));
                spl.removeFirst();

            }

        }
        inputFile.close();
        return spl[0].toFloat();
    }
}


bool ioMapData::getExistsSecondFinish(QString country, QString trackName)
{
    QList<QString> list;
    QList<QString> spl;
    //Automatically determine the platform Windows or Linux to change the paths
      //   #ifdef __linux__
            QString path ("/home/pi/KTracks/"+country+"/"+trackName); // Opens the embeded KML file/txt
     //    #elif _WIN32
    //         QString path (":/KTracks/"+country+"/"+trackName); // Opens the embeded KML file/txt
    //     #else

    //     #endif
    QFile inputFile(path);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        //qDebug() <<"Open successful";
        QTextStream in(&inputFile);
        while (!in.atEnd()) // Reads line and puts it in a string + Debug output of the string
        {
            QString line = in.readLine();
           //qDebug() << line ;
            if(line.contains("STARTFINISH2", Qt::CaseInsensitive))
            {
                inputFile.close();
                return true;
            }

        }
        inputFile.close();
        return false;
    }
}

bool ioMapData::getTrackExists(QString country, QString trackName)
{
    //Automatically determine the platform Windows or Linux to change the paths
     //    #ifdef __linux__
            QDir directory("/home/pi/KTracks/"+country+"/");
     //    #elif _WIN32
     //        QDir directory(":/KTracks/"+country+"/");
    //     #else

    //     #endif

    //qDebug() <<"Directory " << directory;
    QStringList images = directory.entryList(QStringList(),QDir::Files);
    foreach(QString filename, images)
    {
        if(filename == trackName)
        {
            return true;
        }
    }
    return false;
}
