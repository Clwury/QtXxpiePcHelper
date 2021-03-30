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

private:
    bool m_pressed;
    QPoint m_point;

    QLabel *m_label;
    QImage *m_image;
    QLineEdit *m_userName;
    QLineEdit *m_passWord;
    QPushButton *m_login;
    networkrequest *m_request;

    void initUI();
    void initSignalSlots();
};
#endif // MAINWINDOW_H
