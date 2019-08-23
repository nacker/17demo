#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    //核心控件
    //    QTextEdit *textEdit = new QTextEdit(this);
    label = new QLabel(this);
    label->move(0, 0);
    //    label->setText("");
    label->resize(390, 35);


    btn = new QPushButton(this);
    btn->setText("选择文件夹目录");
    btn->move(0, 30);
    btn->resize(150, 30);
    connect(btn,&QPushButton::clicked,this,&MainWindow::on_pushButton_clicked);


    resLabel = new QLabel(this);
    resLabel->move(5, 80);
//    resLabel->setText("代码统计中...");
    resLabel->resize(390, 35);
    resLabel->setAlignment(Qt::AlignCenter);


}

MainWindow::~MainWindow()
{

}

void MainWindow::on_pushButton_clicked()
{

    QString srcDirPath = QFileDialog::getExistingDirectory(
                this, "choose src Directory",
                "/");



    if (srcDirPath.isEmpty()){
        return;
    }else{
        //          qDebug() << "srcDirPath=" << srcDirPath;
        srcDirPath += "/";

        label->setText(srcDirPath);

        QtConcurrent::run(this,&MainWindow::startThread);
    }
}

void MainWindow::startThread()
{
    QString srcDirPath = label->text();

    Count myCount;
    myCount.saveFileToMap(srcDirPath.toStdString());
//        myCount.printFilename();
    int cnts;
    cnts = myCount.getAllLine();
//    qDebug() << "cnts=" << cnts;
//    std::cout << cnts << std::endl;

    int moneyCount = 150000 - cnts;

    resLabel->setText("您已经写了" + QString::number(cnts,10) + "行纯纯的代码,离万元哥还差" + QString::number(moneyCount,10) + "行");
}
