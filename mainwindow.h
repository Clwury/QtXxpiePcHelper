#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QFile>
#include "networkrequest.h"
#include "home.h"

#ifdef Q_OS_MACOS
    #include "unixhome.h"
#endif

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import <AppKit/NSWindow.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 鼠标拖动
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    // 登录
    void accountLogin();
    // 事件过滤
    bool eventFilter(QObject *object, QEvent *event);

private:
    bool m_pressed;
    QPoint m_point;

    QLabel *m_label;
    QLabel *m_close_label;
    QImage m_close_img;
    QImage m_close_hover_img;
    QLineEdit *m_userName;
    QLineEdit *m_passWord;
    QPushButton *m_login;
    NetworkRequest *m_request;

    void initUI();
    void initSignalSlots();
};
#endif // MAINWINDOW_H
