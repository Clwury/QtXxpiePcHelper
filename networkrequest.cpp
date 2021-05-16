#include "networkrequest.h"

QString NetworkRequest::token = "";

NetworkRequest::NetworkRequest(QObject *parent) : QObject(parent)
{
    qDebug() << MACHINE_ID;
    qDebug() << PLATFORM;
    networkAccessManager = new QNetworkAccessManager;
    qDebug() << networkAccessManager->supportedSchemes();
}

QJsonObject NetworkRequest::get(const QString &url, const QJsonObject &params, const bool &async)
{
    QString baseUrl = BASE + url;
    qDebug() << "Get Url: " << baseUrl;
    QUrl _url(baseUrl);
    QUrlQuery query;
    // 遍历params
    QJsonObject::const_iterator i = params.constBegin();
    QJsonObject::const_iterator e = params.constEnd();
    while (i != e) {
//        qDebug() << "key" << i.key();
//        qDebug() << "value" << i.value();
        if (i.value().isDouble())
        {
            query.addQueryItem(i.key(), QString::number(i.value().toDouble()));
        } else {
            query.addQueryItem(i.key(), i.value().toString());
        }
        i++;
    }
    // 添加必要参数
    if (!token.isEmpty())
    {
        query.addQueryItem("token", token);
    }
    if (!params.contains("platform"))
    {
        query.addQueryItem("platform", PLATFORM);
    }
    if (!params.contains("machine_id"))
    {
        query.addQueryItem("machine_id", MACHINE_ID);
    }

    qDebug() << "<<< Get params: " << query.toString();
    _url.setQuery(query);
    QNetworkRequest networkRequest;
    networkRequest.setUrl(_url);
    networkReply = networkAccessManager->get(networkRequest);

    // 开启事件循环,同步请求
    if (!async)
    {
        QEventLoop eventLoop;
        QTimer timer;
        connect(networkAccessManager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
        connect(&timer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);
        timer.start(3000);
        eventLoop.exec();

        if (!timer.isActive())
        {
            networkReply->abort();
            QJsonObject response
            {
                {"error", "Request TimeOut"}
            };
            return response;
        }
    } else {
        // 异步待定
    }

    // response状态码
    QVariant responseStatusCode = networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
//    if (responseStatusCode.isValid())
//    {
    qDebug() << "Post Response Status Code: " << responseStatusCode.toInt();
//    }

    QByteArray byteArray = networkReply->readAll();
//    qDebug() << byteArray;
    // 解析为Json
    QJsonParseError jsonPareError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(byteArray, &jsonPareError);
    if (jsonPareError.error != QJsonParseError::NoError)
    {
        qDebug() << "response Json 解析失败";
        return QJsonObject
        {
            {"error", "Json Parse Error"}
        };
    }
    if (jsonDocument.isObject())
    {
        QJsonObject responseObject = jsonDocument.object();
        // 遍历response
//        qDebug() << "<<<<<";
        QJsonObject::const_iterator i = responseObject.constBegin();
        QJsonObject::const_iterator e = responseObject.constEnd();
        while (i != e) {
//            qDebug() << i.key() << ":" << i.value();
            i++;
        }
//        qDebug() << ">>>>>";
        if (responseObject.value("result").isObject())
        {
            return responseObject.value("result").toObject();
        } else if (responseObject.value("result").isArray()) {
            return QJsonObject
            {
                {"result", responseObject.value("result")}
            };
        } else if (responseObject.value("result").isString()) {
            return QJsonObject
            {
                {"result", responseObject.value("result")}
            };
        }

    }
    return QJsonObject
    {
        {"error", "Get Request Error"},
        {"code", responseStatusCode.toInt()}
    };
}

QJsonObject NetworkRequest::post(const QString &url, QJsonObject &params, const bool &async)
{
    QString baseUrl = BASE + url;
    qDebug() << "Post Url: " << baseUrl;
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
    if (!token.isEmpty())
    {
        params.insert("token", token);
    }
    if (!params.contains("platform"))
    {
        params.insert("platform", PLATFORM);
    }
    if (!params.contains("machine_id"))
    {
        params.insert("machine_id", MACHINE_ID);
    }

    qDebug() << "Post params: " << params;
    QJsonDocument requestDocumet;
    requestDocumet.setObject(params);
    QByteArray requestByte = requestDocumet.toJson(QJsonDocument::Compact);

    QNetworkRequest networkRequest;
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    networkRequest.setUrl(_url);
    networkReply = networkAccessManager->post(networkRequest, requestByte);

    // 开启事件循环,同步请求
    if (!async)
    {
        QEventLoop eventLoop;
        QTimer timer;
        connect(networkAccessManager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
        connect(&timer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);
        timer.start(3000);
        eventLoop.exec();

        if (!timer.isActive())
        {
            networkReply->abort();
            return QJsonObject
            {
                {"error", "Request TimeOut"}
            };
        }
    } else {
        // 异步待定
    }

    QVariant responseStatusCode = networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    qDebug() << "Post Response Status Code: " << responseStatusCode.toInt();
    QByteArray byteArray = networkReply->readAll();
//    qDebug() << byteArray;
    // 解析为Json
    QJsonParseError jsonPareError;
    QJsonDocument responseDocument = QJsonDocument::fromJson(byteArray, &jsonPareError);
    if (jsonPareError.error != QJsonParseError::NoError)
    {
        qDebug() << "response Json 解析失败";
        return QJsonObject
        {
            {"error", "Json Parse Error"}
        };
    }
    if (responseDocument.isObject())
    {
        QJsonObject responseObject = responseDocument.object();
        // 遍历response
//        qDebug() << "<<<<<";
        QJsonObject::const_iterator i = responseObject.constBegin();
        QJsonObject::const_iterator e = responseObject.constEnd();
        while (i != e) {
//            qDebug() << i.key() << ":" << i.value();
            i++;
        }
//        qDebug() << ">>>>>";
        if (!responseObject.contains("result"))
        {
            return responseObject;
        } else if (responseObject.value("result").isObject()) {
            return responseObject.value("result").toObject();
        } else if (responseObject.value("result").isArray()) {
            return QJsonObject
            {
                {"result", responseObject.value("result")}
            };
        } else if (responseObject.value("result").isString()) {
            return QJsonObject
            {
                {"result", responseObject.value("result")}
            };
        }

    }
    return QJsonObject
    {
        {"error", "Request Error"},
        {"code", responseStatusCode.toInt()}
    };
}

void NetworkRequest::cacheToken(const QString _token)
{
    token = _token;
    qDebug() << token << "token 更新成功";
    QString cachePath = QStandardPaths::displayName(QStandardPaths::CacheLocation);
    qDebug() << "cache path" << cachePath;
    QDir dir;
    dir.cd(cachePath);
//    qDebug() << dir.entryList();
    QFile *file = new QFile("Certificate");
    bool open = 0;
    if (!dir.entryList().contains("Certificate"))
    {
        open = file->open(QIODevice::WriteOnly | QIODevice::Text);

    } else {
        open = file->open(QIODevice::WriteOnly | QIODevice::Text | QFile::Truncate);
    }
    if (open)
    {
        QTextStream out(file);
        out << token;
        file->close();
        delete file;
    }
}

QByteArray NetworkRequest::getImage(const QString &url, const bool &async)
{
    QNetworkRequest networkRequest;
    networkRequest.setUrl(url);
    networkReply = networkAccessManager->get(networkRequest);

    // 事件循环,同步请求
    if (!async)
    {
        QEventLoop eventLoop;
        QTimer timer;
        connect(networkAccessManager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
        connect(&timer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);
        timer.start(3000);
        eventLoop.exec();

        if (!timer.isActive())
        {
            networkReply->abort();
            return QByteArray();
        }
    } else {
        // 异步待定
    }

    QVariant responseStatusCode = networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if (networkReply->error() == QNetworkReply::NoError)
    {
        QByteArray byteArray = networkReply->readAll();
        return byteArray;
    }
    return QByteArray();
}
