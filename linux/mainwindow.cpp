#include "mainwindow.h"

using std::cout;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
//    1. 初始化控件
    setupView();
//    2. 初始化数据
    setupData();
}

void MainWindow::setupView()
{
    mainWidget = new QWidget(this);
    this->setCentralWidget(mainWidget);
    QHBoxLayout *H = new QHBoxLayout(mainWidget);

    listView = new QListView(mainWidget);
    listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    textEdit = new QTextEdit(this);

    H->addWidget(listView);
    H->addWidget(textEdit);

    mainWidget->setLayout(H);


    connect(listView,SIGNAL(clicked(QModelIndex)),this,SLOT(showClick(QModelIndex)));


    /* status bar */
    QStatusBar *sb = statusBar();
//    self.setst
    QLabel *l = new QLabel();
    l->setText("<font color=red>QQ:648959</font>");
    sb->addWidget(l);
}

void MainWindow::setupData()
{
    ItemModel = new QStandardItemModel(this);
    Items = new QStandardItemModel(this);

    // 如果当前操作系统为windows系统的话
        // 修改控制台的编码为utf8，防止中文乱码
//    if ( QSysInfo::productType() == "windows" ||
//         QSysInfo::productType() == "winrt" ) {
//         system( "chcp 65001" );
//    }else {
//         qDebug() << "我是Linux";
//    }

    QString path = ":/res/data.json";
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString value = file.readAll();
    file.close();

    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(),&parseJsonErr);
    if(!(parseJsonErr.error == QJsonParseError::NoError))
    {
        qDebug()<<tr("解析json文件错误！");
        return;
    }
    QJsonObject jsonObject = document.object();
    if(jsonObject.contains(QStringLiteral("status")))
    {
        QJsonValue arrayValue = jsonObject.value(QStringLiteral("status"));
        if(arrayValue.isArray())
        {
            QJsonArray array = arrayValue.toArray();

            for(int i=0;i<array.size();i++)
            {
                QJsonValue iconArray = array.at(i);
                QJsonObject icon = iconArray.toObject();
                QString id = icon["id"].toString();
                QString title = icon["title"].toString();
                QString desc = icon["desc"].toString();

                QStandardItem *item = new QStandardItem(title);
                ItemModel->appendRow(item);

                QStandardItem *descitem = new QStandardItem(desc);
                Items->appendRow(descitem);
//                qDebug()<<"id="<<id<<"iconTxt="<<iconTxt<<"iconName="<<iconName;
            }

            listView->setModel(ItemModel);
        }
    }
}

void MainWindow::showClick(QModelIndex index)
{
    int num = index.row();

    QString qstring = Items->item(num)->text();
    textEdit->setText(qstring);

    QClipboard *board = QApplication::clipboard();
    board->setText(index.data().toString());//将qstring复制到剪切板
//    QString str = board->text(); //从剪切板中取出复制的值
}

MainWindow::~MainWindow()
{
//    delete ui;
}
