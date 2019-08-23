#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    w.resize(400, 400);   //设置主窗体大小
    w.setWindowTitle("代码行数统计工具");  //设置主窗体标签

//    w.move(50, 10);//设置窗口的位置

    // 设置对话框icon
    w.setWindowIcon(QIcon(":/png/myico.ico"));

    w.show();

    return a.exec();
}
