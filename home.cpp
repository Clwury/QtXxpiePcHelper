#include <QToolBar>
#include <QMacToolBar>
#include <QMacNativeWidget>
#include <QLabel>
#include "home.h"

home::home(QWidget *parent) : QMainWindow(parent)
{
#ifdef Q_OS_MACOS
    this->setUnifiedTitleAndToolBarOnMac(true);
#endif
    initUI();
    resize(1100, 700);
    // 设置窗口位置
    QScreen *screen = this->screen();
    qDebug() << screen->size();
    move((screen->size().width() - this->width()) / 2, (screen->size().height() - this->height()) / 2);
    initSignalSlots();
}

void home::initUI()
{
//    QWidget *widget = new QWidget();
//    widget->setFixedHeight(30);
//    QHBoxLayout *hLayout = new QHBoxLayout;
//    hLayout->setContentsMargins(0, 10, 0, 10);
//    QLabel *label = new QLabel("相册");
//    hLayout->addWidget(label, 0, Qt::AlignHCenter);
//    widget->setLayout(hLayout);
//    widget->setStyleSheet("border:2px solid red;");
//    QToolBar *toolBar = new QToolBar;
//    toolBar->addWidget(widget);
//    toolBar->setFloatable(false);
//    addToolBar(Qt::TopToolBarArea, toolBar);
    // mac 标题栏
    QMacToolBar *m_toolBar = new QMacToolBar(this);
//    QIcon logo_icon;
//    QImage logo_img;
//    logo_img.load(":/images/ic_login_logo--imgs.png");
//    logo_icon.addPixmap(QPixmap::fromImage(logo_img).scaledToWidth(180, Qt::SmoothTransformation));
//    qDebug() << logo_icon.availableSizes();
//    QMacToolBarItem *m_toolBarItem = new QMacToolBarItem;
//     m_toolBarItem->setStandardItem(QMacToolBarItem::NoStandardItem);
//    m_toolBarItem->setIcon(logo_icon);
//    QList<QMacToolBarItem *> toolBarItemList;

//    QMacToolBarItem *m_toolBarItem_1 = new QMacToolBarItem;
//    m_toolBarItem_1->setText("相册");
//    toolBarItemList.append(m_toolBarItem_1);
//    toolBarItemList.append(m_toolBarItem);
//    m_toolBar->setItems(toolBarItemList);

    m_toolBar->attachToWindow(this->window()->windowHandle());

    // page content
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(0, 0, 0, 0);

    QWidget *top_widget = new QWidget;

    top_widget->setFixedHeight(42);
    QWidget *bottom_widget = new QWidget;

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->setContentsMargins(0, 0, 0, 0);
    QImage m_image;
    m_image.load(":/images/ic_login_logo--imgs.png");
    QLabel *m_label = new QLabel;
    m_label->setPixmap(QPixmap::fromImage(m_image).scaledToHeight(36, Qt::SmoothTransformation));
    hLayout->addStretch(1);
    hLayout->addWidget(m_label);
    hLayout->addStretch(4); // fshgojdsgfodpgkdf[ogjdfgiodfjgidfgnjdfjlkjnjk
    top_widget->setLayout(hLayout);

    top_widget->setStyleSheet("border:2px solid black;");
    bottom_widget->setStyleSheet("border:2px solid red;");

    vLayout->addWidget(top_widget);
    vLayout->addWidget(bottom_widget);

    QWidget *centerWidget = new QWidget;
    centerWidget->setLayout(vLayout);
    setCentralWidget(centerWidget);

    // 原生api
//    NSView *view = (NSView *) this->winId();
//    NSWindow *window = [view window];
}

void home::initSignalSlots()
{

}
