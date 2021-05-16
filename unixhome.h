#ifndef UNIXHOME_H
#define UNIXHOME_H

#include <QMainWindow>
#include <QScreen>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPainterPath>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QListView>
#include <QStandardItemModel>
#include <QJsonArray>
#include <QScrollBar>
#include <QEvent>
#include <QMouseEvent>

#include "customsearchbar.h"
#include "networkrequest.h"
#include "itemdelegate.h"

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import <AppKit/NSWindow.h>

class unixhome : public QMainWindow
{
    Q_OBJECT
public:
    explicit unixhome(QWidget *parent = nullptr);

protected:
    // 事件过滤
    bool eventFilter(QObject *object, QEvent *event);

signals:

private:
    NetworkRequest *m_request;

    QHBoxLayout *MainContentLayout;
    QHBoxLayout *hLayout;
    QListView *albumListView;
    QStandardItemModel *albumListModel;

    QWidget *imageListWidget;
    QVBoxLayout *imageListLayout;
//    QListView *imageListView;
    QList<QListView *> list;
    QList<QWidget *> albumTabList;
    QWidget *albumTabWidget;
    QHBoxLayout *albumTabHLayout;
    QWidget *albumBottomTabWidget;
//    QStandardItemModel *imageModel;
//    ItemDelegate *imageDelegate;
//    QScrollBar *imageVerticalScrollBar;

    QList<QJsonObject> openedAlbumInfoList;
    int focusAlbumIndex;
    int hoverTabIndex;
    bool tabCloseState;
    int focusAlbumCount;
    QJsonObject focusAlbumInfo;
//    QString focusAlbumId;
//    QString firstOpenAlbumName;
    QListView *focusAlbumImageListView;
//    int focusAlbumImageCount;
//    int focusAlbumPageNo;
//    int openedAlbumCount;

    void initUI();
    void initSignalSlots();
    void initData();
    void initAlbumList(const QJsonObject &albumList); // 加载相册列表
    void openAlbum(const QModelIndex &index); // 进入相册
    void addAlbumTabBar(const QString &, const bool &); // 添加相册tabBar
    QListView * initAlbumImageList(const QString &, const QString &); // 初始化相册图片列表
    void focusAlbum(const int &); // 聚焦已打开相册
    void loadThumbnail(const QJsonObject &, const int &); // 分页加载缩略图
    void onScrollBarValueChanged(const int &); // 图片列表下拉加载
};

#endif // UNIXHOME_H
