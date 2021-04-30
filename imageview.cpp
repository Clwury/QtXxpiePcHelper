#include "imageview.h"

QString md5(const QString &str);

ImageView::ImageView()
{

}

ImageView::ImageView(const ImageView &imageView)
{
    state = imageView.state;
    style = imageView.style;
    cachePath = imageView.cachePath;
    urlThumbnail = imageView.urlThumbnail;
    fileName = imageView.fileName;
    loadingPixmap = imageView.loadingPixmap;
    succeedPixmap = imageView.succeedPixmap;
//    networkManager = new QNetworkAccessManager;
}

ImageView::~ImageView()
{

}

ImageView::ImageView(QString url_thumbnail, QString file_name) : urlThumbnail(url_thumbnail), fileName(file_name)
{
    state = STATE::loading;
    style = STYLE::contain;

    // 设置缓存目录
    cachePath = QStandardPaths::displayName(QStandardPaths::CacheLocation);
    QDir dir(cachePath + QDir::separator() + "thumbnail");
    if (!dir.exists())
    {
        dir.mkdir(cachePath + QDir::separator() + "thumbnail");
    }
    networkManager = new QNetworkAccessManager;

    // 判断是否有缓存
    QString thumbnailMd5 = md5(urlThumbnail);
    QFile file(cachePath + QDir::separator() + thumbnailMd5);
    if (!file.exists())
    {
        qDebug() << "start request---" << urlThumbnail;
        reply = networkManager->get(QNetworkRequest(QUrl(urlThumbnail)));
        connect(reply, &QNetworkReply::finished, [&] {
            pixmapLoad();
        });
//        connect(reply, &QNetworkReply::finished, this, &ImageView::pixmapLoad);
    } else {
        if (file.open(QIODevice::ReadOnly))
        {
            QByteArray bytes = file.readAll();
            succeedPixmap.loadFromData(bytes);
            state = STATE::succeed;
        }
    }
}

int ImageView::getState()
{
    return state;
}

QString ImageView::getUrlThumbnail()
{
    return urlThumbnail;
}

QString ImageView::getFileName()
{
    return fileName;
}

QPixmap ImageView::getSucceedPixmap()
{
    return succeedPixmap;
}

void ImageView::pixmapLoad()
{
    qDebug() << "请求完成";
    // 获取图片数据
    if (reply->error() == QNetworkReply::NoError)
    {
        qDebug() << "开始写入缓存";
        QByteArray bytes = reply->readAll();
        succeedPixmap.loadFromData(bytes);
        state = STATE::succeed;
        // 写入缓存
        QString thumbnailMd5 = md5(urlThumbnail);
        QFile file(cachePath + QDir::separator() + thumbnailMd5);
        if (!file.exists())
        {
            file.open(QIODevice::WriteOnly);
            file.close();
        }
        if (file.open(QIODevice::Truncate))
        {
            file.write(bytes);
        }
        file.close();
    } else {
        state = STATE::failed;
        qDebug() << "图片加载失败";
    }
//    networkManager->deleteLater();
}
