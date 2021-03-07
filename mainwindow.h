#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <iostream>
#include <QMainWindow>
#include <QQuickWidget>
#include <QQuickView>
#include <QWindow>
//#include <QCheckBox>
//#include <QRadioButton>
//#include <QPlainTextEdit>
//#include <QPushButton>
#include <QDebug>
#include <QWidget>
#include <QPoint>
#include <QQmlContext>
//#include <QStack>
//#include <QQueue>
//#include <QMap>
//#include <QTime>
//#include <QTimer>

//QT_BEGIN_NAMESPACE
//namespace Ui { class MainWindow; }
//QT_END_NAMESPACE
//using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT
//    Q_PROPERTY(QPoint point READ point WRITE setPoint)
//    QML_ELEMENT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Q_INVOKABLE QPoint point();
    Q_INVOKABLE void setPoint(const QPoint &point);
    Q_INVOKABLE QString userName();
    Q_INVOKABLE void setUserName(const QString &userName);
//    void mousePressEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);

private slots:
//    void on_checkBox_clicked(bool checked);

//    void on_checkBox_2_clicked(bool checked);

//    void on_checkBox_3_clicked(bool checked);
//    void on_checkBoxUnder(bool checked);

//    void on_checkBoxItalic(bool checked);

//    void on_checkBoxBold(bool checked);

//    void setTextFontColor();

//    void on_timer_timeout();

private:
//    Ui::MainWindow *ui;
//    QWidget *widget;
//    QCheckBox *checkBoxUnder;
//    QCheckBox *checkBoxItalic;
//    QCheckBox *checkBoxBold;
//    QRadioButton *radioBtnRed;
//    QRadioButton *radioBtnBlue;
//    QRadioButton *radioBtnWhite;
//    QPlainTextEdit *plainTextEdit;
//    QPushButton *pushBtnSignIn;
//    QPushButton *pushBtnCancel;
//    int ms = 10;
//    QTimer *timer;
//    void iniUI();
//    void iniSignalSlots();

    QQuickView *m_quickView;
    QWidget *m_qWidget;
//    QQuickWidget *m_quickWidget;
//    bool m_pressed;
    QPoint m_point;
    QString m_userName;

};
#endif // MAINWINDOW_H
