#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
//    , ui(new Ui::MainWindow)
{
//    setupUi(this);
    iniUI();
    iniSignalSlots();
    setWindowTitle("你好,世界");
}

MainWindow::~MainWindow()
{
    //    delete ui;
}

void MainWindow::on_checkBoxUnder(bool checked)
{
    QFont font = plainTextEdit->font();
    font.setUnderline(checked);
    plainTextEdit->setFont(font);
}

void MainWindow::on_checkBoxItalic(bool checked)
{
    QFont font = plainTextEdit->font();
    font.setItalic(checked);
    plainTextEdit->setFont(font);
}

void MainWindow::on_checkBoxBold(bool checked)
{
    QFont font = plainTextEdit->font();
    font.setBold(checked);
    plainTextEdit->setFont(font);
}

void MainWindow::setTextFontColor()
{
    QPalette plet = plainTextEdit->palette();
    if (radioBtnRed->isChecked())
        plet.setColor(QPalette::Text, Qt::red);
    else if (radioBtnBlue->isChecked())
        plet.setColor(QPalette::Text, Qt::blue);
    else if (radioBtnWhite->isChecked())
        plet.setColor(QPalette::Text, Qt::white);
    else
        plet.setColor(QPalette::Text, Qt::black);
    plainTextEdit->setPalette(plet);
}

void MainWindow::iniUI()
{
    // 创建checkBox,水平布局
    checkBoxUnder = new QCheckBox(tr("Underline"));
//    checkBoxUnder->metaObject()->className();
    checkBoxItalic = new QCheckBox(tr("Italic"));
    checkBoxBold = new QCheckBox(tr("Bold"));
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    hLayout1->addWidget(checkBoxUnder);
    hLayout1->addWidget(checkBoxItalic);
    hLayout1->addWidget(checkBoxBold);
    // 创建radioButton,水平布局
    radioBtnRed = new QRadioButton(tr("Red"));
    radioBtnRed->setChecked(true);
    radioBtnBlue = new QRadioButton(tr("Blue"));
    radioBtnWhite = new QRadioButton(tr("White"));
    QHBoxLayout *hLayout2 = new QHBoxLayout;
    hLayout2->addWidget(radioBtnRed);
    hLayout2->addWidget(radioBtnBlue);
    hLayout2->addWidget(radioBtnWhite);
    // 创建pushButton,水平布局
    pushBtnSignIn = new QPushButton(tr("登录"));
    pushBtnCancel = new QPushButton(tr("取消"));
    QHBoxLayout *hLayout3 = new QHBoxLayout;
    hLayout3->addWidget(pushBtnSignIn);
    hLayout3->addStretch();
    hLayout3->addWidget(pushBtnCancel);
    // 创建文本框
    plainTextEdit = new QPlainTextEdit;

    qint8 i = -2;
    Q_UNUSED(i);
    cerr << "nidemingzhi" << endl;
    qDebug() << QT_VERSION;
    qint8 a = 0;
    Q_UNUSED(a);
    QList<QString> qList;
    qList << "1" << "2";
    qList.append("td");
    qList.append("tr");
    qDebug() << qList << qList.insert(2, "th") << qList << qList.isEmpty() << qList.size();
    QQueue<int> queue;
    queue.enqueue(0);
    queue.enqueue(1);
    while (!queue.isEmpty()) {
        qDebug() << queue.dequeue();
    }
    QMap<QString, int> map;
    map["liu"] = 0;
    map.insert("cai", 1);
    map.remove("cai");
    qDebug() << map;


    plainTextEdit->setPlainText("Hello,World\nit\'s my demo");
    QFont font = plainTextEdit->font();
    font.setPointSize(20);
    plainTextEdit->setFont(font);
    // 创建主布局
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);
    vLayout->addWidget(plainTextEdit);
    vLayout->addLayout(hLayout3);

    widget = new QWidget();
    this->setCentralWidget(widget);
    widget->setLayout(vLayout);
}

void MainWindow::iniSignalSlots()
{
    connect(checkBoxUnder, &QCheckBox::clicked, this, &MainWindow::on_checkBoxUnder);
    connect(checkBoxItalic, &QCheckBox::clicked, this, &MainWindow::on_checkBoxItalic);
    connect(checkBoxBold, &QCheckBox::clicked, this, &MainWindow::on_checkBoxBold);
    connect(radioBtnRed, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    connect(radioBtnBlue, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    connect(radioBtnWhite, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    connect(pushBtnCancel, &QPushButton::clicked, this, &MainWindow::close);
}
