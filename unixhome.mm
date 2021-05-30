#include "unixhome.h"

unixhome::unixhome(QWidget *parent) : QMainWindow(parent)
{
    initUI();
    initSignalSlots();
//    focusAlbumId = "";
//    focusAlbumImageCount = 0;
//    focusAlbumPageNo = 0;
//    openedAlbumCount = 0;
    focusAlbumIndex = -1;
    hoverTabIndex = -1;
    tabCloseState = false;
//    focusAlbumCount = 0;
    initData();
    // 初始化多相册Tab栏
    albumTabHLayout = new QHBoxLayout;
    albumTabHLayout->setContentsMargins(0, 0, 0, 0);
    albumTabHLayout->setSpacing(0);
    albumTabWidget = new QWidget;
    albumTabWidget->setLayout(albumTabHLayout);
    // 初始化底部状态栏
    QHBoxLayout *albumBottomTabHLayout = new QHBoxLayout;
    albumBottomTabHLayout->setContentsMargins(5, 0, 0, 0);
    albumBottomTabHLayout->setSpacing(0);

    QLabel *currentAlbumImgCountLabel = new QLabel;
    currentAlbumImgCountLabel->setObjectName("currentAlbumImgCountLabel");
//    currentAlbumImgCountLabel->setText(QString::number(focusAlbumCount) + "张图片");

    albumBottomTabHLayout->addWidget(currentAlbumImgCountLabel, Qt::AlignLeft);

    albumBottomTabWidget = new QWidget;
    albumBottomTabWidget->setObjectName("albumBottomTabWidget");
    albumBottomTabWidget->setFixedHeight(25);
    albumBottomTabWidget->setStyleSheet("border-top: 1px solid #BBB6B7;");
    albumBottomTabWidget->setLayout(albumBottomTabHLayout);
}

bool unixhome::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress && object->objectName() == "albumTabBar")
    {
        QWidget *eventWidget = static_cast<QWidget *>(object);
        int index = albumTabList.indexOf(eventWidget);
        qInfo() << object->objectName() << "tab click" << index;
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton)
        {
            if (focusAlbumIndex != index)
            {
                focusAlbum(index);
            }
            return true;
        } else {
            return false;
        }
    } else if (event->type() == QEvent::HoverEnter && object->objectName() == "albumTabBar") {
        QWidget *eventWidget = static_cast<QWidget *>(object);
        int index = albumTabList.indexOf(eventWidget);
        qInfo() << object->objectName() << "tab hover enter" << index;
        hoverTabIndex = index;
        if (index == focusAlbumIndex)
        {
            return true;
        } else {
            eventWidget->setStyleSheet("#albumTabBar{background: #C9C4C5;border: 1px solid #BBB6B7;} #albumTabCloseLabel{background: #C9C4C5;}");
            eventWidget->findChild<QLabel *>("albumTabCloseLabel")->setVisible(true);
            eventWidget->findChild<QLabel *>("placeholderLabel")->setVisible(true);
            return true;
        }
    } else if (event->type() == QEvent::HoverLeave && object->objectName() == "albumTabBar") {
        QWidget *eventWidget = static_cast<QWidget *>(object);
        int index = albumTabList.indexOf(eventWidget);
        qInfo() << object->objectName() << "tab hover leave" << index;

        if (index == focusAlbumIndex)
        {
            return true;
        } else if (index != -1) {
            if (!tabCloseState)
            {
                eventWidget->setStyleSheet("#albumTabBar{background: #e9e9e9;border: 1px solid #BBB6B7;} #albumTabCloseLabel{background: #e9e9e9;}");
                eventWidget->findChild<QLabel *>("albumTabCloseLabel")->setVisible(false);
                eventWidget->findChild<QLabel *>("placeholderLabel")->setVisible(false);
            }
            return true;
        }
    }
    if (event->type() == QEvent::MouseButtonPress && object->objectName() == "albumTabCloseLabel") {
//        QLabel *eventLabel = static_cast<QLabel *>(object);
        tabCloseState = true;
        qInfo() << object->objectName() << "tab close click" << hoverTabIndex << openedAlbumInfoList.size();
        if (hoverTabIndex != -1)
        {

            albumTabHLayout->removeWidget(albumTabList.at(hoverTabIndex));
            delete albumTabList.at(hoverTabIndex);
            qInfo() << "remove before" << albumTabList.size();
            albumTabList.removeAt(hoverTabIndex);
            qInfo() << "remove after" << albumTabList.size();

            imageListLayout->removeWidget(list.at(hoverTabIndex));
            delete list.at(hoverTabIndex);
            list.removeAt(hoverTabIndex);
            qInfo() << list.size();

            openedAlbumInfoList.removeAt(hoverTabIndex);
            if (openedAlbumInfoList.size() == 1)
            {
                albumTabWidget->setVisible(false); // 先隐藏tab栏再聚焦Album
            }

            if (hoverTabIndex == openedAlbumInfoList.size())
            {
                focusAlbumInfo = openedAlbumInfoList.at(hoverTabIndex - 1);
                focusAlbum(hoverTabIndex - 1);
            } else {
                focusAlbumInfo = openedAlbumInfoList.at(hoverTabIndex);
                focusAlbum(hoverTabIndex);
            }

            tabCloseState = false;
        }
        return true;
    }
    return QWidget::eventFilter(object, event);
}

void unixhome::initUI()
{
    resize(1200, 800);
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
    MainContentLayout->setSpacing(0);
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
    add_icon.load(":/images/add.png");
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
    album_icon.load(":/images/album.png");
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
    transport_icon.load(":/images/transport.png");
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
    qInfo() << albums;

    // 获取用户信息
    params = QJsonObject{};
    QJsonObject user_info = m_request->get("/sm/getUserInfo", params, false);
//    qDebug() << "用户信息" << user_info;

    // 显示头像
//    qDebug() << "Get Image Source" << user_info.value("icon_photo_url").toString();
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
    albumItemDelegate *albumDelegate = new albumItemDelegate(this);
    albumListView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    albumListView->setFrameShape(QFrame::NoFrame);
    albumListView->setItemDelegate(albumDelegate);
    albumListView->setModel(albumListModel);
    albumListView->setResizeMode(QListView::Adjust);
    albumListView->setViewMode(QListView::ListMode);
    albumListView->setSpacing(5);
    albumListView->setSelectionRectVisible(true);
    albumListView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    albumListView->setStyleSheet("QScrollBar:vertical\
    {\
        width:8px;\
        background:rgba(0,0,0,0);\
        padding-bottom:9px;                        \
        background-position: right;\
    }                                              \
    QScrollBar::handle:vertical                    \
    {                                              \
        width:8px;                                 \
        border-radius: 4px;                       \
        background: #bdbdbd;                        \
    }                                              \
    QScrollBar::handle:vertical:hover             \
    {\
        background: #828282;\
    }\
    QScrollBar::add-line:vertical\
    {\
        height:0px;width:0px;\
        subcontrol-position:bottom;\
    }\
    QScrollBar::sub-line:vertical\
    {\
        height:0px;width:0px;\
        subcontrol-position:top;\
    }");
    albumListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(albumListView, &QListView::clicked, this, &unixhome::openAlbum);

    QVBoxLayout *albumListLayout = new QVBoxLayout;
    albumListLayout->setContentsMargins(0, 20, 2, 0);
    albumListLayout->addWidget(albumListView);

    QWidget *albumListWidget = new QWidget;
    albumListWidget->setLayout(albumListLayout);
    albumListWidget->setObjectName("albumListWidget");
    albumListWidget->setFixedWidth(260);
//    albumListWidget->setStyleSheet("border:1px solid green;");
    albumListWidget->setStyleSheet("#albumListWidget{border-right:1px solid #eaeaea;}");
    MainContentLayout->addWidget(albumListWidget);

//    qDebug() << "相册列表: " << albumList.value("albums");
//    qDebug() << "相册数量: " << albumList["count"];
    QJsonArray albums = albumList.value("albums").toArray();
    if (albums.size() > 0)
    {
        ImageView *albumsView[albums.size()];
        for (int i = 0; i < albums.size(); i++)
        {
            const QJsonObject albumObject = albums[i].toObject();
    //        qDebug() << "相册名: " << albumObject["task_name"];
            qInfo() << "share_photo_url:" << albumObject.value("share_photo_url");
            albumsView[i] = new ImageView(albumObject.value("share_photo_url").toString(), albumObject.value("task_name").toString(), ImageView::TYPE::albumCover, -1);
            QStandardItem *albumItem = new QStandardItem;
    //        albumItem->setSizeHint(QSize(0, 20));
    //        albumItem->setText(albumObject["task_name"].toString());
    //        albumItem->setData(albumObject, Qt::UserRole);
            albumItem->setData(QVariant::fromValue(albumsView[i]), Qt::UserRole);
            albumItem->setData(ImageView::STATE::loading, Qt::UserRole + 1);
            albumItem->setData(albumObject, Qt::UserRole + 2);
            albumListModel->appendRow(albumItem);
        }
    }
}

void unixhome::openAlbum(const QModelIndex &modelIndex)
{
    try {

        qDebug() << "进入相册" << modelIndex.data(Qt::UserRole + 2).toJsonObject()["shoot_task_id"] << modelIndex.data(Qt::UserRole).toJsonObject()["task_name"];
        QJsonObject albumInfo = modelIndex.data(Qt::UserRole + 2).toJsonObject();
        QString albumId = albumInfo["shoot_task_id"].toString();
        QString albumName = albumInfo["task_name"].toString();

        // 相册已打开则聚焦
        foreach (QJsonObject obj, openedAlbumInfoList) {
            if (obj.value("album_id").toString() == albumId)
            {
                focusAlbum(openedAlbumInfoList.indexOf(obj));
                return;
            }
        }
        QListView *imageListView;

        if (openedAlbumInfoList.isEmpty())
        {

    //        focusAlbumId = albumId;
    //        firstOpenAlbumName = albumName;

            imageListView = initAlbumImageList(albumId, albumName);

            list.append(imageListView);

            // 添加图片缩略图列表
            imageListLayout = new QVBoxLayout;
            imageListLayout->setContentsMargins(0, 0, 0, 0);
            imageListLayout->setSpacing(5);

            imageListLayout->addWidget(albumTabWidget);
    //        albumTabWidget->installEventFilter(this);
            imageListLayout->addWidget(imageListView);

            imageListWidget = new QWidget;
            imageListWidget->setLayout(imageListLayout);
            imageListWidget->setObjectName("imageListWidget");
    //        imageListWidget->setStyleSheet("#imageListWidget{border:1px solid #eaeaea;}");
            MainContentLayout->addWidget(imageListWidget);

        } else {
            // 打开多个相册
            qDebug() << "打开多个相册" << imageListWidget->width() << openedAlbumInfoList.size() + 1 << imageListWidget->width() / (openedAlbumInfoList.size() + 1);
            imageListView = initAlbumImageList(albumId, albumName);
            // 隐藏其他相册列表
            foreach (QListView *item, list)
            {
                item->setVisible(false);
            }
            list.append(imageListView);

    //        QMutableListIterator<QWidget *> i(albumTabList); // QMutableListIterator遍历时进行修改
    //        while (i.hasNext()) {
    //            albumTabWidget->layout()->removeWidget(i.next());
    //            delete i.next();
    //            i.remove();
    //        }

            if (albumTabList.size() == 0)
            {
                // 首次添加两个
                addAlbumTabBar(openedAlbumInfoList.at(0).value("album_name").toString(), false);
                addAlbumTabBar(albumName, true);
            } else {
                if (!albumTabWidget->isVisible())
                {
                    albumTabWidget->setVisible(true);
                }
                foreach (QWidget *w, albumTabList) {
                    w->setStyleSheet("#albumTabBar{background: #e9e9e9;border: 1px solid #ddd;} #albumTabCloseLabel{background: #e9e9e9;}");
                }
                addAlbumTabBar(albumName, true);
            }

            imageListLayout->addWidget(imageListView);
        }

        albumBottomTabWidget->findChild<QLabel *>("currentAlbumImgCountLabel")->setText(QString::number(focusAlbumInfo.value("count").toInt()) + " 张图片");
        if (imageListLayout->findChild<QWidget *>("albumBottomTabWidget") == nullptr)
        {
            imageListLayout->addWidget(albumBottomTabWidget);
        }
    } catch (...) {
        qFatal("catch(...)");
    }
}

void unixhome::addAlbumTabBar(const QString &albumName, const bool &isFocus)
{
    QWidget *albumTabBar = new QWidget;
    albumTabBar->setObjectName("albumTabBar");
    albumTabBar->setFixedHeight(25);
    // 关闭按钮
    QLabel *albumTabCloseLabel = new QLabel;
    albumTabCloseLabel->setObjectName("albumTabCloseLabel");
    QImage albumTabCloseImg;
    albumTabCloseImg.load(":/images/tab_close.png");
    albumTabCloseLabel->setPixmap(QPixmap::fromImage(albumTabCloseImg).scaledToWidth(18, Qt::SmoothTransformation));
    albumTabCloseLabel->setObjectName("albumTabCloseLabel");
    albumTabCloseLabel->setFixedSize(18, 18);
    albumTabCloseLabel->setAlignment(Qt::AlignCenter);
//    albumTabCloseLabel->setStyleSheet("border: 1px solid #91BD91;");
    if (isFocus)
    {
        foreach (QWidget *w, albumTabList) {
            w->findChild<QLabel *>("albumTabCloseLabel")->setVisible(false);
            w->findChild<QLabel *>("placeholderLabel")->setVisible(false);
        }
    }
    albumTabCloseLabel->setVisible(isFocus);
    albumTabCloseLabel->setAttribute(Qt::WA_Hover, true);
    albumTabCloseLabel->installEventFilter(this);

    // 相册名
    QLabel *albumTabNameLabel = new QLabel;
    albumTabNameLabel->setFixedHeight(20);
    QFontMetrics fontMetrics(albumTabNameLabel->font());
    albumTabNameLabel->setText(fontMetrics.elidedText(albumName, Qt::ElideRight, 100));
//    albumTabNameLabel->setStyleSheet("border: 1px solid #91BD91;");
    albumTabNameLabel->setAlignment(Qt::AlignCenter);
    albumTabNameLabel->setStyleSheet("background: transparent");

    // 空白占位符,保持相册名居中
    QLabel *placeholderLabel = new QLabel;
    placeholderLabel->setObjectName("placeholderLabel");
    placeholderLabel->setFixedSize(18, 18);
    placeholderLabel->setStyleSheet("background: transparent");
    placeholderLabel->setVisible(isFocus);

    QHBoxLayout *albumTabBarLayout = new QHBoxLayout;
    albumTabBarLayout->setContentsMargins(5, 0, 5, 0);
    albumTabBarLayout->setSpacing(0);
//    albumTabBarLayout->addWidget(albumTabCloseLabel, 0, Qt::AlignLeft);
//    albumTabBarLayout->addWidget(albumTabNameLabel, 0, Qt::AlignCenter);
    albumTabBarLayout->addWidget(albumTabCloseLabel);
    albumTabBarLayout->addStretch();
    albumTabBarLayout->addWidget(albumTabNameLabel);
    albumTabBarLayout->addStretch();
    albumTabBarLayout->addWidget(placeholderLabel);
    albumTabBar->setLayout(albumTabBarLayout);

//    albumTab->setFixedSize(imageListWidget->width() / list.size(), 20);
    QString albumTabBarStyle;
    if (isFocus)
    {
        albumTabBarStyle = "#albumTabBar{background: #eeefee;} #albumTabCloseLabel{background: #eeefee;}";
    } else {
        albumTabBarStyle = "#albumTabBar{background: #e9e9e9;border: 1px solid #BBB6B7;} #albumTabCloseLabel{background: #e9e9e9;}";
    }

    albumTabBar->setStyleSheet(albumTabBarStyle);
    albumTabList.append(albumTabBar);
//    albumTabWidget->layout()->addWidget(albumTabBar);
    albumTabHLayout->addWidget(albumTabBar);
    albumTabBar->setAttribute(Qt::WA_Hover, true); // 开启hover事件
    albumTabBar->installEventFilter(this);
    qInfo() << "添加tab";
//    imageListLayout->addWidget(albumTabWidget); // 添加相册Tab栏ddfdsfdsfdsfsdf
}

QListView * unixhome::initAlbumImageList(const QString &albumId, const QString &albumName)
{
    // 获取子相册信息
    QJsonObject params
    {
        {"album_id", albumId}
    };
    QJsonObject subAlbums = m_request->get("/pm/querySubAlbums", params, false);
    qInfo() << "子相册信息: " << subAlbums;

    // 子相册信息
    QJsonArray subAlbumsArr = subAlbums.value("result").toArray();

    QListView *imageListView = new QListView;
    QStandardItemModel *imageModel = new QStandardItemModel;
    ItemDelegate *imageDelegate = new ItemDelegate(this);
    imageListView->setFrameShape(QFrame::NoFrame);
    imageListView->setItemDelegate(imageDelegate);
    imageListView->setSpacing(15);
    imageListView->setModel(imageModel);
    imageListView->setViewMode(QListView::IconMode);
    imageListView->setResizeMode(QListView::Adjust);
    imageListView->setSelectionRectVisible(true);
    imageListView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    imageListView->setDragEnabled(false);
    imageListView->setStyleSheet("QScrollBar:vertical\
    {\
        width:8px;\
        background:rgba(0,0,0,0);\
        padding-bottom:9px;                        \
        background-position: right;\
    }                                              \
    QScrollBar::handle:vertical                    \
    {                                              \
        width:8px;                                 \
        border-radius: 4px;                       \
        background: #bdbdbd;                        \
    }                                              \
    QScrollBar::handle:vertical:hover             \
    {\
        background: #828282;\
    }\
    QScrollBar::add-line:vertical\
    {\
        height:0px;width:0px;\
        subcontrol-position:bottom;\
    }\
    QScrollBar::sub-line:vertical\
    {\
        height:0px;width:0px;\
        subcontrol-position:top;\
    }");
    imageListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    focusAlbumImageListView = imageListView;

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

    if (albumImages.contains("items"))
    {
        // 添加相册信息
        QJsonObject object {
            {"album_id", albumId},
            {"album_name", albumName},
            {"count", albumImages["count"].toInt()},
//            {"page_no", 1},
            {"sub_albums", subAlbumsArr}
        };
        focusAlbumInfo = object;
        openedAlbumInfoList.append(object);

        QMap<QString, int> map;
        map.insert("loaded_index", subAlbumsArr.size()); // 相册图片加载索引
        map.insert("page_no", 1); // 相册图片页数加载索引
        openedAlbumLoaded.append(map);
        focusAlbumIndex = openedAlbumInfoList.size() - 1;

        ImageView *addImage = new ImageView("", "点击或拖拽上传", ImageView::TYPE::addImageBtn, -1);
        QStandardItem *addImageModelItem = new QStandardItem;
        addImageModelItem->setData(QVariant::fromValue(addImage), Qt::UserRole);
        addImageModelItem->setData(ImageView::STATE::succeed, Qt::UserRole + 1);
        static_cast<QStandardItemModel *>(focusAlbumImageListView->model())->appendRow(addImageModelItem);
        // 加载子相册
        loadSubAlbums(subAlbumsArr);
        // 加载缩略图
        loadThumbnail(albumImages, 1);
    //    qDebug() << "图片数量" << albumImages["count"];
    //    focusAlbumImageCount = albumImages["count"].toInt();

        // 下拉滚动加载
        QScrollBar *imageVerticalScrollBar = imageListView->verticalScrollBar();
        connect(imageVerticalScrollBar, &QScrollBar::valueChanged, this, &unixhome::onScrollBarValueChanged);
    }

    return imageListView;
}

void unixhome::focusAlbum(const int &index)
{
    // 相册tab栏切换
    foreach (QWidget *w, albumTabList) {
        w->setStyleSheet("#albumTabBar{background: #e9e9e9;border: 1px solid #BBB6B7;} #albumTabCloseLabel{background: #e9e9e9;}");
        w->findChild<QLabel *>("albumTabCloseLabel")->setVisible(false);
        w->findChild<QLabel *>("placeholderLabel")->setVisible(false);
    }
    if (albumTabList.size() > 0)
    {
        albumTabList.at(index)->setStyleSheet("#albumTabBar{background: #eeefee;} #albumTabCloseLabel{background: #eeefee;}");
        albumTabList.at(index)->findChild<QLabel *>("albumTabCloseLabel")->setVisible(true);
        albumTabList.at(index)->findChild<QLabel *>("placeholderLabel")->setVisible(true);
    }
    // 显示相册切换
    for (auto item : list)
    {
        item->setVisible(false);
    }
//            imageListWidget->layout()->addWidget(albumTabWidget);
    focusAlbumImageListView = list.at(index);
    focusAlbumIndex = index;
    focusAlbumInfo = openedAlbumInfoList.at(index);
    list.at(index)->setVisible(true);
    albumBottomTabWidget->findChild<QLabel *>("currentAlbumImgCountLabel")->setText(QString::number(focusAlbumInfo.value("count").toInt()) + " 张图片");
    qInfo() << "focus album success" << index;
}

void unixhome::loadSubAlbums(const QJsonArray &subAlbums)
{
    if (subAlbums.size() > 0)
    {
        ImageView *subAlbumsView[subAlbums.size()];
        for (int i = 0; i < subAlbums.size(); i++) {
            QJsonObject subAlbumItem = subAlbums[i].toObject();
            subAlbumsView[i] = new ImageView("", subAlbumItem.value("task_sub_name").toString(), ImageView::TYPE::subAlbum, -1);
            QStandardItem *subAlbumModelItem = new QStandardItem;
            subAlbumModelItem->setData(QVariant::fromValue(subAlbumsView[i]), Qt::UserRole);
            subAlbumModelItem->setData(ImageView::STATE::succeed, Qt::UserRole + 1);
            static_cast<QStandardItemModel *>(focusAlbumImageListView->model())->appendRow(subAlbumModelItem);
        }
    }
}

void unixhome::loadThumbnail(const QJsonObject &albumImages, const int &pageNo)
{
    Q_UNUSED(pageNo);
    int count = albumImages["items"].toArray().size();
    ImageView *images[count];
    int i = 0;
    for (auto image : albumImages["items"].toArray())
    {
        QJsonObject imageItem = image.toObject();
//        qDebug() << "图片名: " << imageItem.value("file_name");
        images[i] = new ImageView(imageItem["url_thumbnail"].toString(), imageItem ["file_name"].toString(), ImageView::TYPE::image, ++openedAlbumLoaded[focusAlbumIndex]["loaded_index"]);
        connect(images[i], &ImageView::loadCompleted, this, &unixhome::updateListRow);
        QStandardItem *imageModelItem = new QStandardItem;
//        qDebug() << "picture info" << images[i]->getFileName();
        imageModelItem->setData(QVariant::fromValue(images[i]), Qt::UserRole);
        imageModelItem->setData(ImageView::STATE::loading, Qt::UserRole + 1);
//        imageModel->appendRow(imageModelItem);
        static_cast<QStandardItemModel *>(focusAlbumImageListView->model())->appendRow(imageModelItem);
        i++;
    }
}

void unixhome::updateListRow(const int &index, const int &state)
{
    QModelIndex i = focusAlbumImageListView->model()->index(index, 0, QModelIndex());
//    QVariant variant = i.data(Qt::UserRole);
//    ImageView *item = variant.value<ImageView *>();
//    albumListModel->setData(i, item->getPixmap(), Qt::UserRole + 1);
    focusAlbumImageListView->model()->setData(i, ImageView::STATE(state), Qt::UserRole + 1);
    qInfo() << index << ImageView::STATE(state);
}

void unixhome::onScrollBarValueChanged(const int &value)
{
//    qDebug() << "scrollBar maxValue" << focusAlbumImageListView->verticalScrollBar()->maximum();
//    qDebug() << value;
//     imageListView->model()->rowCount();
    QStandardItemModel *imageModel = dynamic_cast<QStandardItemModel *>(focusAlbumImageListView->model());
    qInfo() << "已加载数量" << imageModel->rowCount() << ", 总数量" << focusAlbumInfo.value("count");
    if (focusAlbumInfo.value("count").toInt() + 1 + focusAlbumInfo.value("sub_albums").toArray().size() == imageModel->rowCount())
    {
        return;
    } else if (value == focusAlbumImageListView->verticalScrollBar()->maximum()) {
        // 判断上一页是否加载完成
        for (int i = 50 * (openedAlbumLoaded[focusAlbumIndex]["page_no"] - 1); i < 50 * openedAlbumLoaded[focusAlbumIndex]["page_no"]; i++)
        {
            QModelIndex index = focusAlbumImageListView->model()->index(i, 0, QModelIndex());
            qInfo() << "panduanjiazai" << index.row() << index.data(Qt::UserRole + 1).toInt();
            if (index.data(Qt::UserRole + 1).toInt() == 0)
            {
                break;
                return;
            }
        }
        // 分页加载
        QJsonObject params
        {
            {"album_id", focusAlbumInfo["album_id"].toString()},
//            {"page_no", focusAlbumInfo["page_no"].toInt() + 1},
            {"page_no", openedAlbumLoaded[focusAlbumIndex]["page_no"] + 1},
            {"page_size", 50},
            {"item_retouch_status", "ALL"},
            {"sub_album_ids", "[]"},
            {"photographer_ids", "[]"}
        };
        QJsonObject albumImages = m_request->get("/pm/queryAlbumItemsPg4PCHelper", params, false);
        if (albumImages.contains("items"))
        {
//            loadThumbnail(albumImages, focusAlbumInfo["page_no"].toInt() + 1);
            loadThumbnail(albumImages, openedAlbumLoaded.at(focusAlbumIndex).value("page_no"));
//            focusAlbumInfo = QJsonObject {
//                {"album_id", focusAlbumInfo.value("album_id").toString()},
//                {"album_name", focusAlbumInfo.value("album_name").toString()},
//                {"count", focusAlbumInfo.value("count").toInt()},
//                {"page_no", focusAlbumInfo.value("page_no").toInt() + 1},
//                {"sub_albums", focusAlbumInfo.value("sub_albums").toArray()}
//            };
            openedAlbumLoaded[focusAlbumIndex]["page_no"]++; // 页面索引加一
            qInfo() << "current album loaded pageNo" << openedAlbumLoaded.at(focusAlbumIndex).value("page_no") << ", " << imageModel->rowCount();
            qInfo() << "current album loaded imageIndex" << openedAlbumLoaded.at(focusAlbumIndex).value("loaded_index");
//            openedAlbumInfoList.replace(focusAlbumIndex, focusAlbumInfo);
        }
    }
}






