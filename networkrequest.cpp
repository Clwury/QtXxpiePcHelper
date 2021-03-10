#include "networkrequest.h"

networkrequest::networkrequest(QObject *parent) : QObject(parent)
{
    qDebug() << MACHINE_ID;
    networkAccessManager = new QNetworkAccessManager;
    qDebug() << networkAccessManager->supportedSchemes();
    //    networkAccessManager
}

void networkrequest::get(const QString &url, const QJsonObject &params)
{
    QString baseUrl = BASE + url;
    QUrl _url(baseUrl);
    QUrlQuery query;
    // 遍历params
    QJsonObject::const_iterator i = params.constBegin();
    QJsonObject::const_iterator e = params.constEnd();
    while (i != e) {
        qDebug() << "key" << i.key();
        qDebug() << "value" << i.value();
        query.addQueryItem(i.key(), i.value().toString());
        i++;
    }
    _url.setQuery(query);
    QNetworkRequest networkRequest;
    networkRequest.setUrl(_url);
    networkReply = networkAccessManager->get(networkRequest);

}

void networkrequest::post(const QString &url, const QJsonObject &params)
{

}

