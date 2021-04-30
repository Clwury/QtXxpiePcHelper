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

signals:

private:
    NetworkRequest *m_request;

    QHBoxLayout *MainContentLayout;
    QHBoxLayout *hLayout;
    QListView *albumListView;
    QStandardItemModel *albumListModel;

    QListView *imageListView;
    QStandardItemModel *imageModel;
    ItemDelegate *imageDelegate;

    void initUI();
    void initSignalSlots();
    void initData();
    void initAlbumList(const QJsonObject &albumList);
    void toAlbum(const QModelIndex &index);
};

#endif // UNIXHOME_H
