#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

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

private:
    bool m_pressed;
    QPoint m_point;

    QLineEdit *m_userName;
    QLineEdit *m_passWord;
    QPushButton *m_login;

    void initUI();
    void initSignalSlots();
};
#endif // MAINWINDOW_H
