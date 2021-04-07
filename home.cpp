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
    this->move((screen->size().width() - this->width()) / 2, (screen->size().height() - this->height()) / 2);
    initUI();
    initSignalSlots();
}

void home::initUI()
{
//    QHBoxLayout *hLayout = new QHBoxLayout;

}

void home::initSignalSlots()
{

}
