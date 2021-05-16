#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QObject>
#include <typeinfo>
#include <QStyleOptionViewItem>
#include "networkrequest.h"

class ImageView : public QObject
{
    Q_OBJECT
public:
    ImageView();
    ImageView(const ImageView &imageView);
    ~ImageView();
    ImageView(QString url_thumbnail, QString file_name, int type);
    enum TYPE {
        image,
        addImageBtn,
        subAlbum
    };

    enum STATE {
        loading,
        succeed,
        failed
    };
    enum STYLE {
        cover,
        contain,
        percentage
    };
    int getType();
    int getState();
    QString getUrlThumbnail();
    QString getFileName();
    QPixmap getPixmap();
    void pixmapLoad();

signals:

public slots:


private:
    int type;
    int state;
    int style;
    QString cachePath; // 缓存目录
    QString urlThumbnail; // 缩略图url
    QString fileName; // 文件名
    QPixmap loadingPixmap;
    QPixmap succeedPixmap;
    QPixmap pixmap;
    QNetworkAccessManager *networkManager;
    QNetworkReply *reply;
};

Q_DECLARE_METATYPE(ImageView)

#endif // IMAGEVIEW_H
