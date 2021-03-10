#include "mainwindow.h"
//#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
//    , ui(new Ui::MainWindow)
{
//    ui->setupUi(this);
//    iniUI();
//    iniSignalSlots();
//    setWindowTitle("你好,世界");

#ifdef Q_OS_MACOS
    this->setUnifiedTitleAndToolBarOnMac(true);
#else
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
#endif
//    WId wid = this->winId();
    this->setFixedSize(400, 300);

//    this->setAttribute(Qt::WA_TranslucentBackground);
//    QWindow *window = this->windowHandle();
//    qDebug() << window;
//    this->setAttribute(Qt::WA_TranslucentBackground, true);
//    this->setWindowOpacity(0.3);
//    m_point = this->pos();
    qDebug() << "窗口起始位置pos" << m_point;
    m_quickView = new QQuickView();
    m_qWidget = QWidget::createWindowContainer(m_quickView, this);
    m_qWidget->resize(400, 300);
    m_quickView->setResizeMode(QQuickView::SizeRootObjectToView);
    m_quickView->setColor(QColor(Qt::transparent));
    m_quickView->rootContext()->setContextProperty("mainWindow", this);
//    qDebug() << m_quickView->initialSize();
    m_quickView->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
//    m_quickView->show();
//    m_quickWidget = new QQuickWidget();
//    m_quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
//    m_quickWidget->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
//    m_quickWidget->rootContext()->setContextProperty("mainWindow", this);

}

MainWindow::~MainWindow()
{
//    delete ui;
    delete m_quickView;
    delete m_qWidget;
//    delete m_quickWidget;
}

QPoint MainWindow::point()
{
    return m_point;
}

void MainWindow::setPoint(const QPoint &point)
{
    if (m_point == point)
    {
        return;
    }
    m_point += point;
    this->move(m_point);
}

QString MainWindow::userName()
{
    return m_userName;
}

void MainWindow::setUserName(const QString &userName)
{
    m_userName = userName;
    qDebug() << m_userName;
}

void MainWindow::login(const QString &userName, const QString &password)
{
    qDebug() << userName << password;
}

//void MainWindow::mousePressEvent(QMouseEvent *event)
//{
//    qDebug() << "press";
//    if (event->button() == Qt::LeftButton)
//    {
//        m_pressed = true;
//        m_point = event->pos();
//        qDebug() << m_point;
//    }
//}

//void MainWindow::mouseMoveEvent(QMouseEvent *event)
//{
//    if (m_pressed)
//    {
//        move(event->pos() - m_point + this->pos());
//    }
//}

//void MainWindow::mouseReleaseEvent(QMouseEvent *event)
//{
//    Q_UNUSED(event);
//    m_pressed = false;
//}


//void MainWindow::on_checkBoxUnder(bool checked)
//{
//    QFont font = plainTextEdit->font();
//    font.setUnderline(checked);
//    plainTextEdit->setFont(font);
//}

//void MainWindow::on_checkBoxItalic(bool checked)
//{
//    QFont font = plainTextEdit->font();
//    font.setItalic(checked);
//    plainTextEdit->setFont(font);
//}

//void MainWindow::on_checkBoxBold(bool checked)
//{
//    QFont font = plainTextEdit->font();
//    font.setBold(checked);
//    plainTextEdit->setFont(font);
//}

//void MainWindow::setTextFontColor()
//{
//    QPalette plet = plainTextEdit->palette();
//    if (radioBtnRed->isChecked())
//        plet.setColor(QPalette::Text, Qt::red);
//    else if (radioBtnBlue->isChecked())
//        plet.setColor(QPalette::Text, Qt::blue);
//    else if (radioBtnWhite->isChecked())
//        plet.setColor(QPalette::Text, Qt::white);
//    else
//        plet.setColor(QPalette::Text, Qt::black);
//    plainTextEdit->setPalette(plet);
//}

//void MainWindow::on_timer_timeout()
//{
//    qDebug() << ms--;
//    if (ms == 0)
//    {
//        timer->stop();
//    }
//}

//void MainWindow::iniUI()
//{
//    // 创建checkBox,水平布局
//    checkBoxUnder = new QCheckBox(tr("Underline"));
////    checkBoxUnder->metaObject()->className();
//    checkBoxItalic = new QCheckBox(tr("Italic"));
//    checkBoxBold = new QCheckBox(tr("Bold"));
//    QHBoxLayout *hLayout1 = new QHBoxLayout;
//    hLayout1->addWidget(checkBoxUnder);
//    hLayout1->addWidget(checkBoxItalic);
//    hLayout1->addWidget(checkBoxBold);
//    // 创建radioButton,水平布局
//    radioBtnRed = new QRadioButton(tr("Red"));
//    radioBtnRed->setChecked(true);
//    radioBtnBlue = new QRadioButton(tr("Blue"));
//    radioBtnWhite = new QRadioButton(tr("White"));
//    QHBoxLayout *hLayout2 = new QHBoxLayout;
//    hLayout2->addWidget(radioBtnRed);
//    hLayout2->addWidget(radioBtnBlue);
//    hLayout2->addWidget(radioBtnWhite);
//    // 创建pushButton,水平布局
//    pushBtnSignIn = new QPushButton(tr("登录"));
//    pushBtnCancel = new QPushButton(tr("取消"));
//    QHBoxLayout *hLayout3 = new QHBoxLayout;
//    hLayout3->addWidget(pushBtnSignIn);
//    hLayout3->addStretch();
//    hLayout3->addWidget(pushBtnCancel);
//    // 创建文本框
//    plainTextEdit = new QPlainTextEdit;

//    qint8 i = -2;
//    Q_UNUSED(i);
//    cerr << "nidemingzhi" << endl;
//    qDebug() << QT_VERSION;
//    qint8 a = 0;
//    Q_UNUSED(a);
//    QList<QString> qList;
//    qList << "1" << "2";
//    qList.append("td");
//    qList.append("tr");
//    qDebug() << qList << qList.insert(2, "th") << qList << qList.isEmpty() << qList.size();
//    QQueue<int> queue;
//    queue.enqueue(0);
//    queue.enqueue(1);
//    while (!queue.isEmpty()) {
//        qDebug() << queue.dequeue();
//    }
//    QMap<QString, int> map;
//    map["liu"] = 0;
//    map.insert("cai", 1);
//    map.remove("cai");
//    qDebug() << map;
//    QListIterator<QString> listIterator (qList);
//    while (listIterator.hasNext()) {
//        qDebug() << listIterator.next();
//    }
//    QString str = "9";
//    bool ok;
//    qDebug() << str.toInt(&ok, 16);
//    float price = 5*3.3;
//    qDebug() << price;
//    str = QString::asprintf("%.3f", price);
//    qDebug() << str;
//    qDebug() << str.toFloat();
//    str = QString::number(12, 2);
//    qDebug() << str;
//    str = "ni   好  ";
//    qDebug() << str.simplified();
//    QTime *t = new QTime();
//    qDebug() << t->currentTime();
//    timer = new QTimer();
//    timer->setInterval(1000);
////    int ti = 1000;
//    connect(timer, &QTimer::timeout, this, &MainWindow::on_timer_timeout);
//    timer->start();


//    plainTextEdit->setPlainText("Hello,World\nit\'s my demo");
//    QFont font = plainTextEdit->font();
//    font.setPointSize(20);
//    plainTextEdit->setFont(font);
//    // 创建主布局
//    QVBoxLayout *vLayout = new QVBoxLayout;
//    vLayout->addLayout(hLayout1);
//    vLayout->addLayout(hLayout2);
//    vLayout->addWidget(plainTextEdit);
//    vLayout->addLayout(hLayout3);

//    widget = new QWidget();
//    this->setCentralWidget(widget);
//    widget->setLayout(vLayout);
//}

//void MainWindow::iniSignalSlots()
//{
//    connect(checkBoxUnder, &QCheckBox::clicked, this, &MainWindow::on_checkBoxUnder);
//    connect(checkBoxItalic, &QCheckBox::clicked, this, &MainWindow::on_checkBoxItalic);
//    connect(checkBoxBold, &QCheckBox::clicked, this, &MainWindow::on_checkBoxBold);
//    connect(radioBtnRed, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
//    connect(radioBtnBlue, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
//    connect(radioBtnWhite, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
//    connect(pushBtnCancel, &QPushButton::clicked, this, &MainWindow::close);
//}
