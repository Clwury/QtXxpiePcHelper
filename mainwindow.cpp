#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
#ifdef Q_OS_MACOS
    this->setUnifiedTitleAndToolBarOnMac(true);
#else
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
#endif

    this->setFixedSize(400, 300);
    initUI();
    initSignalSlots();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initUI()
{
    m_label = new QLabel();
//    m_label->setStyleSheet("border:2px solid red;");
    m_image = new QImage;
    m_image->load(":/images/ic_login_logo--imgs.png");
    QImage scaleImage = m_image->scaledToWidth(200, Qt::FastTransformation);
    m_label->setPixmap(QPixmap::fromImage(scaleImage));
    m_label->setFixedHeight(scaleImage.height());
    m_userName = new QLineEdit;
    m_userName->setPlaceholderText("请输入号码");
    m_userName->setText("18390216081");
//    m_userName->setMaximumWidth(150);
    m_userName->setFixedWidth(150);
    m_passWord = new QLineEdit;
    m_passWord->setEchoMode(QLineEdit::Password);
    m_passWord->setText("123456");
//    m_passWord->setMaximumWidth(150);
    m_passWord->setFixedWidth(150);
    m_login = new QPushButton("登录");
    m_login->setFixedWidth(100);
    m_login->setFixedHeight(40);
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addStretch(4);
    vLayout->addWidget(m_label, 0, Qt::AlignHCenter);
    vLayout->addStretch(3);
    vLayout->addWidget(m_userName, 0, Qt::AlignHCenter);
    vLayout->addStretch(1);
    vLayout->addWidget(m_passWord, 0, Qt::AlignHCenter);
    vLayout->addStretch(1);
    vLayout->addWidget(m_login, 0, Qt::AlignHCenter);
    vLayout->addStretch(4);
//    vLayout->setStretchFactor(m_userName, 1);
//    vLayout->setStretchFactor(m_passWord, 1);
//    vLayout->setStretchFactor(m_login, 2);
    QWidget *centerWidget = new QWidget;
    centerWidget->setLayout(vLayout);
    setCentralWidget(centerWidget);
//    setStyleSheet(":/qss/qss/login.qss");

    // 读取qss样式
    QFile file(":/qss/qss/login.qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString stylesheet = QLatin1String(file.readAll());
        this->setStyleSheet(stylesheet);
        file.close();
    }

    m_request = new networkrequest();
}

void MainWindow::initSignalSlots()
{
    connect(m_login, &QPushButton::clicked, this, &MainWindow::accountLogin);
}

void MainWindow::accountLogin()
{
    qDebug() << "点击登录";
    qDebug() << m_userName->text() << m_passWord->text();
    QString userName = m_userName->text();
    QString password = m_passWord->text();
    QJsonObject params
    {
        {"username", userName}
    };
    QJsonObject response;
    response = m_request->get("/sm/validateElseMachineIsAdmin", params);
    if (response.contains("code") && !response.value("code").toInt())
    {
        qDebug() << "after take" << response;
        QString md5(const QString &str);
        QJsonObject params
        {
            {"username", userName},
            {"platform", PLATFORM},
            {"machine_id", MACHINE_ID},
            {"password", md5(password)}
        };
        response = m_request->post("/photographer/mine/signInByPassword", params);

        // 登录成功
        if (response.contains("token"))
        {
            qDebug() << response.value("token") << "登录成功";
            this->close();
            // 打开主页面

        }
    }
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



