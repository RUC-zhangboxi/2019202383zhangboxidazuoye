#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>  //鼠标事件
#include <Qtimer>       //定时器
#include "defensetowerpit.h"    //防御塔坑类
#include "selectionbox.h"       //选择框类
#include "weapon.h"    //防御塔父类
#include "monster.h"    //怪物类
#include <QLabel>

class MainWindow : public QWidget
{
//    Q_OBJECT
private:
    QVector<DefenseTowerPit*> TowerPitVec;  //防御塔坑数组
    SelectionBox* SelBox = new SelectionBox(":/image/SelectionBox.png"); //选择框类

    QVector<weapon*> DefeTowerVec; //重要武器类

    QVector<Monster*> MonsterVec;           //怪物数组

    void paintEvent(QPaintEvent *);         //绘图事件
    void mousePressEvent(QMouseEvent *);    //鼠标点击事件
//    void mouseMoveEvent(QMouseEvent *);   //鼠标移动事件

    void DrawMapArr(QPainter&);             //用于画出地图函数
    void DrawSelectionBox(QPainter&);       //用于画出选择框
    void DrawDefenseTower(QPainter&);       //画出防御塔
    void DrawMonster(QPainter&);            //画出怪物
    void DrawRangeAndUpgrade(QPainter&);    //画出防御塔攻击范围和升级按钮
    void DrawExplosion(QPainter&);          //画出爆炸效果

    int DisplayRangeX, DisplayRangeY;       //用于记录显示范围的防御塔的坐标
    bool DisplayRange = false;              //用于显示防御塔攻击范围

    struct ExploStr     //爆炸效果结构
    {
        CoorStr coor;   //记录爆炸效果的坐标
        int index = 1;  //记录要显示的图片文件的序号

        int ExplRangeWidth;    //爆炸效果宽高
        int ExplRangeHeight;
        //爆炸效果需要初始化坐标、效果宽高
        ExploStr(CoorStr fcoor, int width, int height) : coor(fcoor), ExplRangeWidth(width), ExplRangeHeight(height) {}
    };

    QVector<ExploStr*> ExploEffectCoor;      //爆炸效果坐标数组

    int money = 1000;   //记录金钱
    QLabel *moneylable = new QLabel(this);   //显示金钱标签控件

    inline bool DeductionMoney(int);         //判断金钱是否足够并刷新标签

    int life = 10;      //生命数量

    int counter = 0;    //用于产生怪物的计数器

    const int RewardMoney = 30; //每次击败怪物获得的金钱数量

    CoorStr *homecoor = new CoorStr(0, 0);  //记录家的坐标，从地图中自动获取

    void IrodMonsProgDefa(CoorStr**, CoorStr**, CoorStr*, int*, QLabel*); //预设两条路产生怪物方案函数

    const int LevelNumber;      //标识关卡

    bool DisplayAllRange = false;  //标识是否显示所有防御塔的攻击范围

public:
    MainWindow(int);            //构造
    ~MainWindow();
};

#endif  //MAINWINDOW_H
