#ifndef NETWORKREQUEST_H
#define NETWORKREQUEST_H

#include <config.h>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QEventLoop>
#include <QTimer>
#include <QStandardPaths>
#include <QDir>

extern const QUuid UID;
extern const QString MACHINE_ID;

class NetworkRequest : public QObject
{
    Q_OBJECT
public:
    explicit NetworkRequest(QObject *parent = nullptr);
    QJsonObject get(const QString &url, const QJsonObject &params, const bool &async);
    QJsonObject post(const QString &url, QJsonObject &params, const bool &async);
    static void cacheToken(const QString token);
    QByteArray getImage(const QString &url, const bool &async);
signals:

private:
    QNetworkAccessManager *networkAccessManager;
    QNetworkReply *networkReply;
    static QString token;
};

#endif // NETWORKREQUEST_H
