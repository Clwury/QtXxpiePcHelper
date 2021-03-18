#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
#ifdef Q_OS_MACOS
    this->setUnifiedTitleAndToolBarOnMac(true);
#else
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
#endif

    this->resize(500, 375);
    initUI();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initUI()
{
    m_userName = new QLineEdit;
    m_userName->setPlaceholderText("请输入姓名");
    m_passWord = new QLineEdit;
    m_passWord->setEchoMode(QLineEdit::Password);
    m_login = new QPushButton("login");
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(m_userName);
    vLayout->addWidget(m_passWord);
    vLayout->addWidget(m_login);
    QWidget *centerWidget = new QWidget;
    centerWidget->setLayout(vLayout);
    setCentralWidget(centerWidget);
    setStyleSheet(QString("QMainWindow{ background-color: #d1d1d1; }"));
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_pressed = true;
        m_point = event->pos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_pressed)
    {
        move(event->pos() - m_point + this->pos());
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    m_pressed = false;
}



