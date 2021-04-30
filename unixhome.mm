#include "unixhome.h"

unixhome::unixhome(QWidget *parent) : QMainWindow(parent)
{
    initUI();
    initSignalSlots();
    initData();
}

void unixhome::initUI()
{
    resize(1100, 700);
    setStyleSheet("background-color: #eeefee;");
    // 设置窗口位置
    QScreen *screen = this->screen();
    qDebug() << screen->size();
    move((screen->size().width() - this->width()) / 2, (screen->size().height() - this->height()) / 2);
    NSView *view = (NSView *) this->winId();
    NSWindow *window = [view window];
    qDebug() << window;
    window.titlebarAppearsTransparent = YES;

    window.styleMask = NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable
                       | NSWindowStyleMaskResizable | NSWindowStyleMaskTitled
                       | NSWindowStyleMaskFullSizeContentView;

//    NSTitlebarAccessoryViewController *vc = [[NSTitlebarAccessoryViewController alloc] init];
//    vc.view = [[NSView alloc] initWithFrame:((NSView *)window.contentView).frame];
//    [window addTitlebarAccessoryViewController:vc];

    // page content
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(0, 30, 0, 0);
    vLayout->setSpacing(10);
    QWidget *centerWidget = new QWidget;
    centerWidget->setLayout(vLayout);
    setCentralWidget(centerWidget);

    QWidget *top_widget = new QWidget;
    top_widget->setObjectName("top_widget");
    QWidget *bottom_widget = new QWidget;
//    top_widget->setContentsMargins(0, 0, 0, 0);
    top_widget->setFixedHeight(48);
//    top_widget->setStyleSheet("border:2px solid black");
    bottom_widget->setStyleSheet("border:2px solid red;");
    bottom_widget->setStyleSheet("background: #ffffff;");
    // 设置阴影
//    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(top_widget);
//    effect->setOffset(0, 8);
//    effect->setColor(QColor(0,0,0,20));
//    effect->setBlurRadius(12);
//    top_widget->setStyleSheet("#top_widget{background-color: #eeefee;}");
//    top_widget->setGraphicsEffect(effect);

    vLayout->addWidget(top_widget);
    vLayout->addWidget(bottom_widget);

    hLayout = new QHBoxLayout;
//    hLayout->setSpacing(0);
    hLayout->setContentsMargins(28, 0, 0, 0);
    hLayout->setAlignment(Qt::AlignLeft);
    top_widget->setLayout(hLayout);

    QImage logo_img;
    logo_img.load(":/images/ic_login_logo--imgs.png");
    QLabel *logo_label = new QLabel;
    logo_label->setPixmap(QPixmap::fromImage(logo_img).scaledToHeight(36, Qt::SmoothTransformation));
    logo_label->setMaximumWidth(180);
    hLayout->addWidget(logo_label);


//    QLineEdit *search_line = new QLineEdit;
//    search_line->setFixedWidth(100);
//    hLayout->addWidget(search_line);
    hLayout->addSpacing(80);
    customSearchBar *custom_search_bar = new customSearchBar;
//    custom_search_bar->setStyleSheet("border: 2px solid yellow;");
    custom_search_bar->setFixedWidth(320);
    hLayout->addWidget(custom_search_bar);

    // main Content
    MainContentLayout = new QHBoxLayout;
    MainContentLayout->setContentsMargins(0, 0, 0, 0);
    MainContentLayout->setAlignment(Qt::AlignLeft);
    bottom_widget->setLayout(MainContentLayout);
    QWidget *side_bar = new QWidget;
    side_bar->setObjectName("side_bar");
    MainContentLayout->addWidget(side_bar);
    side_bar->setFixedWidth(72);
    side_bar->setStyleSheet("#side_bar{border-right:1px solid #eaeaea;}");
//    side_bar->setStyleSheet("border:1px solid red;");

    QVBoxLayout *side_bar_vLayout = new QVBoxLayout;
    side_bar_vLayout->setContentsMargins(0, 20, 0, 0);
    side_bar_vLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    side_bar_vLayout->setSpacing(0);
    side_bar->setLayout(side_bar_vLayout);

    // 协同添加
    QImage add_icon;
    add_icon.load(":/images/add.svg");
    QLabel *add_icon_label = new QLabel;
    add_icon_label->setPixmap(QPixmap::fromImage(add_icon).scaledToHeight(20, Qt::SmoothTransformation));
    add_icon_label->setAlignment(Qt::AlignHCenter);
    side_bar_vLayout->addWidget(add_icon_label);
    side_bar_vLayout->addSpacing(5);
    QLabel *add_text_label = new QLabel("协同");
    add_text_label->setStyleSheet("font-size: 13px;color: #494949;");
    side_bar_vLayout->addWidget(add_text_label);
    side_bar_vLayout->addSpacing(25);

    // 相册
    QImage album_icon;
    album_icon.load(":/images/album.svg");
    QLabel *album_icon_label = new QLabel;
    album_icon_label->setPixmap(QPixmap::fromImage(album_icon).scaledToHeight(20, Qt::SmoothTransformation));
    album_icon_label->setAlignment(Qt::AlignHCenter);
    side_bar_vLayout->addWidget(album_icon_label);
    side_bar_vLayout->addSpacing(5);
    QLabel *album_text_label = new QLabel("相册");
    album_text_label->setStyleSheet("font-size: 13px;color: #494949;");
    side_bar_vLayout->addWidget(album_text_label);
    side_bar_vLayout->addSpacing(25);

    // 传输列表
    QImage transport_icon;
    transport_icon.load(":/images/transport.svg");
    QLabel *transport_icon_label = new QLabel;
    transport_icon_label->setPixmap(QPixmap::fromImage(transport_icon).scaledToHeight(20, Qt::SmoothTransformation));
    transport_icon_label->setAlignment(Qt::AlignHCenter);
    side_bar_vLayout->addWidget(transport_icon_label);
    side_bar_vLayout->addSpacing(5);
    QLabel *transport_text_label = new QLabel("传输");
    transport_text_label->setStyleSheet("font-size: 13px;color: #494949;");
    side_bar_vLayout->addWidget(transport_text_label);
    side_bar_vLayout->addSpacing(25);

}

void unixhome::initSignalSlots()
{

}

void unixhome::initData()
{
    m_request = new NetworkRequest();
    // 获取相册列表
    QJsonObject params
    {
        {"type", "PHOTO_ALBUM"},
        {"page_size", 1000},
        {"page_no", 1}
    };
    QJsonObject albums = m_request->get("/pm/queryAlbumsPg", params, false);
    qDebug() << albums;

    // 获取用户信息
    params = QJsonObject{};
    QJsonObject user_info = m_request->get("/sm/getUserInfo", params, false);
    qDebug() << "用户信息" << user_info;

    // 显示头像
    qDebug() << "Get Image Source" << user_info.value("icon_photo_url").toString();
    QLabel *icon_photo_label = new QLabel;
    QImage icon_photo_img;
    QPixmap icon_photo_pixmap;
    QByteArray icon_photo_bytes = m_request->getImage(user_info.value("icon_photo_url").toString(), false);
    if (!icon_photo_bytes.isNull())
    {
        icon_photo_pixmap.loadFromData(icon_photo_bytes);
    //    icon_photo_label->setPixmap(icon_photo_pixmap.scaledToHeight(32, Qt::SmoothTransformation));
        icon_photo_pixmap.scaledToHeight(32, Qt::SmoothTransformation);
        QPixmap circle_icon_photo(32, 32);
        circle_icon_photo.fill(Qt::transparent);
        QPainterPath painterPath;
        painterPath.addEllipse(0, 0, 32, 32);
        QPainter painter(&circle_icon_photo);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        painter.setClipPath(painterPath);
        painter.drawPixmap(0, 0, 32, 32, icon_photo_pixmap);
        icon_photo_label->setPixmap(circle_icon_photo);

        icon_photo_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        icon_photo_label->setContentsMargins(0, 0, 28, 0);
        hLayout->addSpacing(240);
        hLayout->addWidget(icon_photo_label);
    }
    initAlbumList(albums);
}

void unixhome::initAlbumList(const QJsonObject &albumList)
{
    albumListView = new QListView;
    albumListModel = new QStandardItemModel;
    albumListView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    albumListView->setFrameShape(QFrame::NoFrame);
    albumListView->setModel(albumListModel);
    albumListView->setSelectionRectVisible(true);
    albumListView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    albumListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(albumListView, &QListView::doubleClicked, this, &unixhome::toAlbum);

    QVBoxLayout *albumListLayout = new QVBoxLayout;
    albumListLayout->setContentsMargins(0, 20, 10, 0);
    albumListLayout->addWidget(albumListView);
    QWidget *albumListWidget = new QWidget;
    albumListWidget->setObjectName("albumListWidget");
    MainContentLayout->addWidget(albumListWidget);
    albumListWidget->setFixedWidth(250);
//    albumListWidget->setStyleSheet("border:1px solid green;");
    albumListWidget->setLayout(albumListLayout);
    albumListWidget->setStyleSheet("#albumListWidget{border-right:1px solid #eaeaea;}");

    qDebug() << "相册列表: " << albumList.value("albums");
    qDebug() << "相册数量: " << albumList["count"];
    QJsonArray albums = albumList.value("albums").toArray();
    for (auto album : albums)
    {
        const QJsonObject albumObject = album.toObject();
        qDebug() << "相册名: " << albumObject["task_name"];
        QStandardItem *albumItem = new QStandardItem;
        albumItem->setSizeHint(QSize(0, 20));
        albumItem->setText(albumObject["task_name"].toString());
        albumItem->setData(albumObject, Qt::UserRole);
        albumListModel->appendRow(albumItem);
    }
}

void unixhome::toAlbum(const QModelIndex &modelIndex)
{
    qDebug() << modelIndex.data(Qt::UserRole).toJsonObject()["shoot_task_id"] << modelIndex.data(Qt::UserRole).toJsonObject()["task_name"];
    QJsonObject albumInfo = modelIndex.data(Qt::UserRole).toJsonObject();
    QString albumId = albumInfo["shoot_task_id"].toString();
    // 获取子相册信息
    QJsonObject params
    {
        {"album_id", albumId}
    };
    QJsonObject subAlbums = m_request->get("/pm/querySubAlbums", params, false);
    qDebug() << "子相册信息: " << subAlbums;

    // 获取相册图片
    params = QJsonObject
    {
        {"album_id", albumId},
        {"page_no", 1},
        {"page_size", 50},
        {"item_retouch_status", "ALL"},
        {"sub_album_ids", "[]"},
        {"photographer_ids", "[]"}
    };
    QJsonObject albumImages = m_request->get("/pm/queryAlbumItemsPg4PCHelper", params, false);
    qDebug() << albumImages["count"];

    imageListView = new QListView;
    imageModel = new QStandardItemModel;
    imageDelegate = new ItemDelegate;
    imageListView->setItemDelegate(imageDelegate);
    imageListView->setSpacing(15);
    imageListView->setModel(imageModel);
    imageListView->setDragEnabled(false);

    for (auto image : albumImages["items"].toArray())
    {
        QJsonObject imageItem = image.toObject();
        qDebug() << "图片名: " << imageItem.value("file_name");
        ImageView imageView(imageItem["url_thumbnail"].toString(), imageItem["file_name"].toString());
        break;
//        QStandardItem *imageModelItem = new QStandardItem;
//        imageModelItem->setData(QVariant::fromValue(imageView), Qt::UserRole);
//        imageItemModel->appendRow(imageModelItem);
    }
}




