#ifndef NETWORKREQUEST_H
#define NETWORKREQUEST_H

//#include <QDebug>
//#include <QString>
#include <config.h>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonObject>
#include <QEventLoop>

extern const QUuid UUID;
extern const QString MACHINE_ID;

class networkrequest : public QObject
{
    Q_OBJECT
public:
    explicit networkrequest(QObject *parent = nullptr);
    void get(const QString &url, const QJsonObject &params);
    void post(const QString &url, const QJsonObject &params);

signals:

private:
    QNetworkAccessManager *networkAccessManager;
    QNetworkReply *networkReply;
};

#endif // NETWORKREQUEST_H
