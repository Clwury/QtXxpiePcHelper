#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <iostream>
#include <QMainWindow>
#include <QQuickView>
#include <QWindow>
//#include <QCheckBox>
//#include <QRadioButton>
//#include <QPlainTextEdit>
//#include <QPushButton>
#include <QDebug>
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

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
};
#endif // MAINWINDOW_H
