#include <QToolBar>
#include <QLabel>
#include "home.h"

home::home(QWidget *parent) : QMainWindow(parent)
{
#ifdef Q_OS_MACOS
    this->setUnifiedTitleAndToolBarOnMac(true);
#endif
    resize(1100, 700);
    // 设置窗口位置
    QScreen *screen = this->screen();
    qDebug() << screen->size();
    move((screen->size().width() - this->width()) / 2, (screen->size().height() - this->height()) / 2);
    initUI();
    initSignalSlots();
}

void home::initUI()
{
//    QWidget *widget = new QWidget();
//    widget->setFixedHeight(30);
//    QHBoxLayout *hLayout = new QHBoxLayout;
//    hLayout->setContentsMargins(0, 0, 0, 0);
//    QLabel *label = new QLabel("相册");
//    hLayout->addWidget(label, 0, Qt::AlignHCenter);
//    widget->setLayout(hLayout);
//    widget->setStyleSheet("width: 100%;border:2px solid red;");
//    QToolBar *toolBar = new QToolBar;
//    toolBar->addWidget(widget);
//    toolBar->setFloatable(true);
//    addToolBar(Qt::TopToolBarArea, toolBar);
}

void home::initSignalSlots()
{

}
