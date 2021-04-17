#ifndef PARSEGITHUBDATA_H
#define PARSEGITHUBDATA_H

#include <QString>
#include <QList>


class parsegithubData
{
public:
    QList<QPair<QString,QString>> pairs;
    parsegithubData();
    QList<QString> readTrackData();
    void sortDownloadedFiles();


};

#endif // PARSEGITHUBDATA_H
