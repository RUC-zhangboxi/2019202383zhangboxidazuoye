#include "startfrom.h"
#include "ui_startfrom.h"
#include "mainwindow.h"

StartFrom::StartFrom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartFrom)
{
    ui->setupUi(this);
    setWindowTitle("TOWERDEFENSE");

    //关卡数量
    const int NumLe = 3;

    //按钮数组
    QPushButton* btnarr[NumLe] = {ui->pushButton, ui->pushButton_2, ui->pushButton_3};

    for (int i = 0; i < NumLe; i++)
        connect(btnarr[i], &QPushButton::clicked, [=]()
        {
            MainWindow *mainwindow = new MainWindow(i);
            mainwindow->show();
        });

}

StartFrom::~StartFrom()
{
    delete ui;
}
