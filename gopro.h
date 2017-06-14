#ifndef GOPRO_H
#define GOPRO_H

#include <QObject>
#include <QNetworkReply>


class GoPro : public QObject
{
    Q_OBJECT

public:
    GoPro(QObject *parent = 0);
    Q_INVOKABLE void goprorec(const QString &record);
    Q_INVOKABLE void goProSettings(const int &goProSelect, const QString &goPropass);


public slots:
    void replyFinished(QNetworkReply* reply);
};

#endif // GOPRO_H
