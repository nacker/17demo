#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
//#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include "line.h"

#include<QtConcurrent>//要记得添加该头文件

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QLabel *label;
    QPushButton *btn;

    QLabel *resLabel;

    // 自定义槽函数
    void on_pushButton_clicked();
    void startThread();

};



#endif // MAINWINDOW_H
