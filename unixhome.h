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
#include <iostream>

#include "customsearchbar.h"
#include "networkrequest.h"

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

    QHBoxLayout *hLayout;

    void initUI();
    void initSignalSlots();
    void initData();
};

#endif // UNIXHOME_H
