#include "networkrequest.h"

networkrequest::networkrequest(QObject *parent) : QObject(parent)
{
    qDebug() << MACHINE_ID;
    qDebug() << PLATFORM;
    networkAccessManager = new QNetworkAccessManager;
    qDebug() << networkAccessManager->supportedSchemes();
    //    networkAccessManager
}

QJsonObject networkrequest::get(const QString &url, const QJsonObject &params)
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

    // response状态码
    QVariant responseStatusCode = networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if (responseStatusCode.isValid())
    {
        qDebug() << "响应状态: " << responseStatusCode.toInt();
    }

    QByteArray byteArray = networkReply->readAll();
    qDebug() << byteArray;
    // 解析为Json
    QJsonParseError jsonPareError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(byteArray, &jsonPareError);
    if (jsonPareError.error != QJsonParseError::NoError)
    {
        qDebug() << "response Json 解析失败";
        return QJsonObject{};
    }
    if (jsonDocument.isObject())
    {
        QJsonObject responseObject = jsonDocument.object();
        // 遍历response
        qDebug() << "<<<<<";
        QJsonObject::const_iterator i = responseObject.constBegin();
        QJsonObject::const_iterator e = responseObject.constEnd();
        while (i != e) {
            qDebug() << i.key() << ":" << i.value();
            i++;
        }
        qDebug() << ">>>>>";
        return responseObject;
    }
    return QJsonObject{};
}

QJsonObject networkrequest::post(const QString &url, QJsonObject &params)
{
    QString baseUrl = BASE + url;
    qDebug() << baseUrl;
    QUrl _url(baseUrl);
//    QUrlQuery query;
//    // 遍历params
//    QJsonObject::const_iterator i = params.constBegin();
//    QJsonObject::const_iterator e = params.constEnd();
//    while (i != e) {
//        qDebug() << "key" << i.key();
//        qDebug() << "value" << i.value();
//        query.addQueryItem(i.key(), i.value().toString());
//        i++;
//    }
//    // 添加必要参数
//    query.addQueryItem("platform", PLATFORM);
//    query.addQueryItem("machine_id", MACHINE_ID);

//    _url.setQuery(query);
    if (!params.contains("platform"))
    {
        params.insert("platform", PLATFORM);
    }
    if (!params.contains("machine_id"))
    {
        params.insert("machine_id", MACHINE_ID);
    }

    QJsonDocument requestDocumet;
    requestDocumet.setObject(params);
    QByteArray requestByte = requestDocumet.toJson(QJsonDocument::Compact);

    QNetworkRequest networkRequest;
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    networkRequest.setUrl(_url);
    networkReply = networkAccessManager->post(networkRequest, requestByte);

    // 开启事件循环
    QEventLoop eventLoop;
    connect(networkAccessManager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    QByteArray byteArray = networkReply->readAll();
    qDebug() << byteArray;
    // 解析为Json
    QJsonParseError jsonPareError;
    QJsonDocument responseDocument = QJsonDocument::fromJson(byteArray, &jsonPareError);
    if (jsonPareError.error != QJsonParseError::NoError)
    {
        qDebug() << "response Json 解析失败";
        return QJsonObject{};
    }
    if (responseDocument.isObject())
    {
        QJsonObject reponseObject = responseDocument.object();
        // 遍历response
        qDebug() << "<<<<<";
        QJsonObject::const_iterator i = reponseObject.constBegin();
        QJsonObject::const_iterator e = reponseObject.constEnd();
        while (i != e) {
            qDebug() << i.key() << ":" << i.value();
            i++;
        }
        qDebug() << ">>>>>";
        return reponseObject;
    }
    return QJsonObject{};
}

