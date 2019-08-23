#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QClipboard>

#include <QtDebug>
#include <QMessageBox>
#include <QFileDialog>          //文件对话框控件
#include <QStringList>          //字符串容器
#include <QDir>                 //目录类头文件
#include <QString>

#include <QStringListModel>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QListView>
#include <QTextEdit>
#include <QLabel>
#include <QStatusBar>

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QSysInfo>
#include <cstdlib>
#include <iostream>

#include <QHBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QWidget *mainWidget;
    QListView *listView;
    QTextEdit *textEdit;

public:
    QStandardItemModel *ItemModel;
    QStandardItemModel *Items;

    void setupView();
    void setupData();

private slots:
    void showClick(QModelIndex index);
};

#endif // MAINWINDOW_H
