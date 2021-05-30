#include "imageview.h"

ImageView::ImageView()
{

}

ImageView::ImageView(const ImageView &imageView)
{
    type = imageView.type;
    state = imageView.state;
    style = imageView.style;
    index = imageView.index;
    cachePath = imageView.cachePath;
    urlThumbnail = imageView.urlThumbnail;
    fileName = imageView.fileName;
    loadingPixmap = imageView.loadingPixmap;
    succeedPixmap = imageView.succeedPixmap;
    pixmap = imageView.pixmap;
//    networkManager = new QNetworkAccessManager;
}

ImageView::~ImageView()
{

}

ImageView::ImageView(QString url_thumbnail, QString file_name, int type, int index) : type(type), index(index), urlThumbnail(url_thumbnail), fileName(file_name)
{
    if (type == TYPE::addImageBtn)
    {
        state = STATE::succeed;
        pixmap = QPixmap(":/images/add_image.png").scaledToWidth(60, Qt::SmoothTransformation);
        return;
    } else if (type == TYPE::subAlbum) {
        state = STATE::succeed;
        pixmap = QPixmap(":/images/folder.png").scaledToWidth(80, Qt::SmoothTransformation);
        return;
    }
    state = STATE::loading;
    style = STYLE::contain;
    if (type == TYPE::image)
    {
        pixmap = QPixmap(":/images/img_loading.png").scaledToWidth(120, Qt::SmoothTransformation);
    } else if (type == TYPE::albumCover) {
        pixmap = QPixmap(":/images/con_pic-def-xxp.png").scaledToHeight(36, Qt::SmoothTransformation);
        if (urlThumbnail.isEmpty()) {
            state = STATE::succeed;
            return;
        }
    }

    // 设置缓存目录
    cachePath = QStandardPaths::displayName(QStandardPaths::CacheLocation);
    QDir dir;
    dir.cd(cachePath);
    if (!dir.entryList().contains("thumbnail"))
    {
        dir.mkdir("thumbnail");
    }
//    QDir dir(cachePath + QDir::separator() + "thumbnail");
//    if (!dir.exists())
//    {
//        dir.mkdir(cachePath + QDir::separator() + "thumbnail");
//    }
//    qDebug() << "缓存目录: " << cachePath;
    networkManager = new QNetworkAccessManager;

    // 判断是否有缓存
//    QString thumbnailMd5 = md5(urlThumbnail);
//    QFile file1(cachePath + QDir::separator() + "thumbnail" + QDir::separator() + "1234");
//    qDebug() << "file1 exists" << file1.exists();
    dir.cd("thumbnail");
//    QFile file(cachePath + QDir::separator() + "thumbnail" + QDir::separator() + thumbnailMd5);
//    if (!dir.entryList().contains(thumbnailMd5))
//    {
//    qDebug() << "start request---" << urlThumbnail;
    reply = networkManager->get(QNetworkRequest(QUrl(urlThumbnail)));
    connect(reply, &QNetworkReply::finished, this, &ImageView::pixmapLoad);
//    } else {
//        QFile file(thumbnailMd5);
//        if (file.open(QIODevice::ReadOnly))
//        {
//            QByteArray bytes = file.readAll();
//            succeedPixmap.loadFromData(bytes);
//            state = STATE::succeed;
//        }
    //    }
}

int ImageView::getType()
{
    return type;
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

QPixmap ImageView::getPixmap()
{
    return pixmap;
}

void ImageView::pixmapLoad()
{
    // 获取图片数据
    if (reply->error() == QNetworkReply::NoError)
    {
//        qDebug() << "开始写入缓存";
        QByteArray bytes = reply->readAll();
        QPixmap p;
        if (p.loadFromData(bytes))
        {
            pixmap = p;
            state = STATE::succeed;
        } else {
            if (state == TYPE::image) {
                pixmap = QPixmap(":/images/error.jpg").scaledToWidth(120, Qt::SmoothTransformation);
            }
            state = STATE::failed;
        }
//        // 写入缓存
//        QString thumbnailMd5 = md5(urlThumbnail);
//        qDebug() << "缓存文件名" << thumbnailMd5;
//        QDir dir;
//        dir.cd(cachePath);
//        dir.cd("thumbnail");
//        qDebug() << "absolute path" << dir.makeAbsolute() << dir.absolutePath();
// //       QFile file(cachePath + QDir::separator() + "thumbnail" + QDir::separator() + thumbnailMd5);
//        QFile file(dir.absolutePath() + QDir::separator() + thumbnailMd5);
//        qDebug() << file << "写入文件名";
//        if (!file.exists())
//        {
//            file.open(QIODevice::WriteOnly);
//            file.close();
//        }
//        bool open = file.open(QIODevice::WriteOnly | QIODevice::Truncate);
//        qDebug() << "file opened" << open;
//        if (open)
//        {
//            qDebug() << urlThumbnail << thumbnailMd5 << "cache write bytes complete";
//            file.write(bytes);
//        }
//        file.close();
//        qDebug() << "写入完成";
    } else {
        state = STATE::failed;
        if (state == TYPE::image) {
            pixmap = QPixmap(":/images/error.jpg").scaledToWidth(120, Qt::SmoothTransformation);
        }
    }
    emit loadCompleted(index, state);
    reply->deleteLater();
    networkManager->deleteLater();
}
