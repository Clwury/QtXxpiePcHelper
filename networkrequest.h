#ifndef NETWORKREQUEST_H
#define NETWORKREQUEST_H

#include "config.h"
#include <QDebug>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class networkrequest : public QObject
{
    Q_OBJECT
public:
    explicit networkrequest(QObject *parent = nullptr);
    void get(const QString &url);
//    void post(const )

signals:

private:
    QNetworkAccessManager *networkAccessManager;
    QNetworkRequest networkRequest;
    QNetworkReply *networkReply;
};

#endif // NETWORKREQUEST_H
