#include "networkrequest.h"

networkrequest::networkrequest(QObject *parent) : QObject(parent)
{
    qDebug() << MACHINE_ID;
    qDebug() << PLATFORM;
    networkAccessManager = new QNetworkAccessManager;
    qDebug() << networkAccessManager->supportedSchemes();
    //    networkAccessManager
}

void networkrequest::get(const QString &url, const QJsonObject &params)
{
    QString baseUrl = BASE + url;
    qDebug() << baseUrl;
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
    // 添加必要参数
    query.addQueryItem("platform", PLATFORM);
    query.addQueryItem("machine_id", MACHINE_ID);

    _url.setQuery(query);
    QNetworkRequest networkRequest;
    networkRequest.setUrl(_url);
    networkReply = networkAccessManager->get(networkRequest);

    // 开启事件循环
    QEventLoop eventLoop;
    connect(networkAccessManager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    QByteArray byteArray = networkReply->readAll();
    qDebug() << byteArray;
    return;
}

void networkrequest::post(const QString &url, const QJsonObject &params)
{

}

