#include "mainwindow.h"
#include <QDebug>
#include "globalstruct.h"       //选择框按钮全局结构
#include <cmath>               //数学
#include "board.h"        //板子防御塔类
#include "fork.h"         //叉子御塔类
#include "bell.h"        //喇叭防御塔类
#include "plate.h"          //飞镖防御塔类
#include <QPushButton>

//鼠标点击区域宏
#define MouClickRegion(X, Width, Y, Height)     \
(ev->x() >= (X) && ev->x() <= (X) + (Width) &&  \
ev->y() >= (Y) && ev->y() <= (Y) + (Height))

//计算两点之间距离宏
#define DistBetPoints(X1, Y1, X2, Y2)           \
abs(sqrt((((X1) - (X2)) * ((X1) - (X2))) + (((Y1) - (Y2)) * ((Y1) - (Y2)))))

//用于方便通过格子确定路径点坐标
#define X40(X, Y) ((X) - 1) * 40 + 10, ((Y) - 1) * 40 + 10

//插入怪物  路径点数组名、怪物初始坐标、怪物编号
#define InsterMonster(PathNum, StaCoorNum, MonsterId)     \
MonsterVec.push_back(new Monster(pointarr[PathNum], PathLength[PathNum], X40(staco[StaCoorNum].x, staco[StaCoorNum].y), MonsterId));

//判断金钱是否足够并刷新标签
inline bool MainWindow::DeductionMoney(int money)
{
    if (this->money - money < 0) return true; //判断金钱是否足够
    this->money -= money; //扣除金钱
    moneylable->setText(QString("金钱：%1").arg(this->money)); //刷新标签文本
    return false;
}

//构造
MainWindow::MainWindow(int LevelNumber) : LevelNumber(LevelNumber)
{
    //设置固定窗口大小
    setFixedSize(1040, 640);

    //设置标题
    setWindowTitle("游戏界面");

    //提示胜利标签
    QLabel *victorylable = new QLabel(this);
    victorylable->move(176, 180);
    victorylable->setFont(QFont("宋体", 100));
    victorylable->setText(QString("all clear！"));
    victorylable->hide();

    QTimer* timer2 = new QTimer(this);      //用于插入怪物定时器
    timer2->start(2000);

    connect(timer2,&QTimer::timeout,[=]()
    {
        //根据关卡编号确定执行怪物的路径方案
        switch (LevelNumber)
        {
        case 0:
        {
            //设置路径点
            CoorStr* Waypointarr1[] = {new CoorStr(X40(8, 6)), new CoorStr(X40(2, 6)), new CoorStr(X40(2, 13)), new CoorStr(X40(19, 13)), new CoorStr(X40(19, 9)), new CoorStr(homecoor->x, homecoor->y)};
            CoorStr* Waypointarr2[] = {new CoorStr(X40(20, 5)), new CoorStr(X40(14, 5)), new CoorStr(X40(14, 13)), new CoorStr(X40(19, 13)), new CoorStr(X40(19, 9)),
                                             new CoorStr(homecoor->x, homecoor->y)}; //最后的路径点设为家
            //怪物的四个起始点
            CoorStr staco[] = {CoorStr(8, 0), CoorStr(20, 0), CoorStr(8, -1), CoorStr(20, -1)};

            //每条路径的结点个数
            int PathLength[] = {sizeof(Waypointarr1)/sizeof(CoorStr*), sizeof(Waypointarr1)/sizeof(CoorStr*)};

            IrodMonsProgDefa(Waypointarr1, Waypointarr2, staco, PathLength, victorylable);   //使用预设的两条路产生怪物方案

            break;
        }
        case 1:
        {
            //设置路径点
            CoorStr* Waypointarr1[] = {new CoorStr(X40(4, 7)), new CoorStr(X40(2, 7)), new CoorStr(X40(2, 13)), new CoorStr(X40(5, 13)), new CoorStr(homecoor->x, homecoor->y)};
            CoorStr* Waypointarr2[] = {new CoorStr(X40(11, 8)), new CoorStr(X40(20, 8)), new CoorStr(X40(20, 13)), new CoorStr(X40(6, 13)), new CoorStr(homecoor->x, homecoor->y)};

                                      //怪物的四个起始点
            CoorStr staco[] = {CoorStr(4, 0), CoorStr(11, 0), CoorStr(4, -1), CoorStr(11, -1)};

            //每条路径的结点个数
            int PathLength[] = {sizeof(Waypointarr1)/sizeof(CoorStr*), sizeof(Waypointarr1)/sizeof(CoorStr*)};

            IrodMonsProgDefa(Waypointarr1, Waypointarr2, staco, PathLength, victorylable);   //使用预设的两条路产生怪物方案
            break;
        }

        case 2:
        {
            //设置路径点
            CoorStr* Waypointarr1[] = {new CoorStr(X40(6, 11)), new CoorStr(X40(3, 11)), new CoorStr(X40(3, 7)), new CoorStr(X40(6, 7)),  new CoorStr(X40(6, 4)), new CoorStr(X40(8, 4)),new CoorStr(X40(8, 1)),new CoorStr(homecoor->x, homecoor->y)};
            CoorStr* Waypointarr2[] = {new CoorStr(X40(16, 12)), new CoorStr(X40(21, 12)), new CoorStr(X40(21, 8)),new CoorStr(X40(16, 8)),new CoorStr(X40(16, 1)), new CoorStr(homecoor->x, homecoor->y)};

            //怪物的四个起始点
            CoorStr staco[] = {CoorStr(6, 15), CoorStr(16, 15), CoorStr(6, 16), CoorStr(16, 16)};

            //每条路径的结点个数
            int PathLength[] = {sizeof(Waypointarr1)/sizeof(CoorStr*), sizeof(Waypointarr1)/sizeof(CoorStr*)};

            IrodMonsProgDefa(Waypointarr1, Waypointarr2, staco, PathLength, victorylable);   //使用预设的两条路的产生怪物方案
            break;
        }
        }
    });



    //金钱标签
    moneylable->move(20, 40);       //位置
    setStyleSheet("color:black");   //设置颜色
    moneylable->setFont(QFont("微软雅黑", 24));             //设置金钱标签属性
    moneylable->setText(QString("金钱：%1").arg(money));    //显示金钱信息

    //生命值标签
    QLabel *lifelable = new QLabel(this);
    lifelable->setGeometry(20, 100, 220, 40);   //设置控件位置和大小
    lifelable->setFont(QFont("微软雅黑", 24));
    lifelable->setText(QString("生命：%1").arg(life));

    //定时器每时每刻执行防御塔父类数组的活动函数
    QTimer* timer = new QTimer(this);
    timer->start(120);

    connect(timer,&QTimer::timeout,[=]()
    {
        //防御塔寻找目标怪物的规律：找到最后一个怪物作为目标，目标丢失后找再继续找最后一个目标
        for (auto defei : DefeTowerVec)      //遍历防御塔
        {
            if (!defei->GetAimsMonster())   //目标怪物为空时从后往前遍历怪物数组寻找目标怪物
            {
                for(int i = MonsterVec.size() - 1; i >= 0; i--)
                    if (DistBetPoints(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40,
                        MonsterVec.at(i)->GetX() + (MonsterVec.at(i)->GetWidth() >> 1),
                        MonsterVec.at(i)->GetY() + (MonsterVec.at(i)->GetHeight() >> 1)) <= defei->GetRange())
                    {
                        defei->SetAimsMonster(MonsterVec.at(i));    //设置防御塔的目标怪物
                        break;  //找到后跳出循环
                    }
            }
            else                //当前防御塔拥有目标且怪物在防御塔范围之内时时攻击怪物
                if (DistBetPoints(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40,
                    defei->GetAimsMonster()->GetX() + (defei->GetAimsMonster()->GetWidth() >> 1),
                    defei->GetAimsMonster()->GetY() + (defei->GetAimsMonster()->GetHeight() >> 1)) <= defei->GetRange())
                {
                    //根据每个防御塔的目标怪物计算旋转角度
                    defei->Setturnangle(
                        atan2
                        (
                            defei->GetAimsMonster()->GetY()/* + (defei->GetAimsMonster()->GetHeight() >> 1)*/ - defei->GetUpLeftY() + 40,
                            defei->GetAimsMonster()->GetX()/* + (defei->GetAimsMonster()->GetWidth() >> 1)*/ - defei->GetUpLeftX()
                        ) * 180 / 3.1415 );

                     defei->newBullet();           //拥有目标时一直创建子弹
                }

            //每次循环都判断目标怪物距离防御塔的距离
            if (defei->GetAimsMonster())    //目标怪物不为空
                if (DistBetPoints(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40,
                    defei->GetAimsMonster()->GetX() + (defei->GetAimsMonster()->GetWidth() >> 1),
                    defei->GetAimsMonster()->GetY() + (defei->GetAimsMonster()->GetHeight() >> 1)) > defei->GetRange())
                        defei->SetAimsMonster(NULL);     //超过距离将目标怪物设为空
        }

        //防御塔子弹移动
        for (auto defei : DefeTowerVec)
            defei->BulletMove();

        //怪物移动
        for (auto Moni = MonsterVec.begin(); Moni != MonsterVec.end(); Moni++)
            if((*Moni)->Move()) //怪物走到终点
            {
                delete *Moni;
                MonsterVec.erase(Moni);         //怪物走到终点则删除这个怪物

                life--;
                lifelable->setText(QString("生命：%1").arg(life));

                if (life <= 0) this->close();   //生命值为0时关闭该窗口

                break;
            }

        //判断子弹击中怪物
        for (auto defei : DefeTowerVec)  //防御塔
        {
            auto &tbullvec = defei->GetBulletVec();    //临时存储子弹
            for (auto bullit = tbullvec.begin(); bullit != tbullvec.end(); bullit++)    //子弹
                for (auto monit = MonsterVec.begin(); monit != MonsterVec.end(); monit++)//怪物
                    if ((*bullit)->GetX() + (defei->GetBulletWidth() >> 1) >= (*monit)->GetX() && (*bullit)->GetX() <= (*monit)->GetX() + (*monit)->GetWidth() &&
                       (*bullit)->GetY() + (defei->GetBulletHeight() >> 1) >= (*monit)->GetY() && (*bullit)->GetY() <= (*monit)->GetY() + (*monit)->GetHeight())
                    {   //击中怪物时
                        tbullvec.erase(bullit);     //删除子弹

                        (*monit)->SetHealth((*monit)->GetHealth() - defei->GetAttack());      //敌人血量 = 本身血量减去 当前炮塔攻击力

                        //将击中的怪物中心的坐标插入到爆炸效果数组
                        ExploEffectCoor.push_back(new ExploStr(CoorStr((*monit)->GetX() + ((*monit)->GetWidth() >> 1), (*monit)->GetY() + ((*monit)->GetHeight() >> 1)),
                                                                defei->GetExplRangeWidth(), defei->GetExplRangeHeight()));

                        if ((*monit)->GetHealth() <= 0) //生命值为空时
                        {
                            //判断一下其他防御塔的目标怪物是否和当前防御塔消灭的怪物重复，如果重复，则将那一个防御塔的目标怪物也设为空
                            for (auto defei2 : DefeTowerVec)
                                if (defei2->GetAimsMonster() == *monit)
                                    defei2->SetAimsMonster(NULL);

                            MonsterVec.erase(monit);    //删除怪物
                            money += RewardMoney;       //击败怪物增加金钱
                            moneylable->setText(QString("金钱：%1").arg(money));//刷新标签
                        }


                        goto L1;
                    }
            L1:;
        }

        //显示爆炸效果
        for (auto expli = ExploEffectCoor.begin(); expli != ExploEffectCoor.end(); expli++)
        {
            if((*expli)->index >= 8)
            {
                ExploEffectCoor.erase(expli);
                break;
            }

            (*expli)->index++;
        }

        update();   //绘图
    });
}

//预设的两条路产生怪物方案
void MainWindow::IrodMonsProgDefa(CoorStr** Waypointarr1, CoorStr** Waypointarr2, CoorStr* staco, int* PathLength, QLabel* victorylable)
{
    /*两条路径*/
    CoorStr** pointarr[] = {Waypointarr1, Waypointarr2};

    /*插入怪物*/
    if(counter >= 1 && counter <= 12)
    {
        InsterMonster(0, 0, 1); //第几条路径、第几个起始点、怪物编号
    }
    else if(counter > 12 && counter <= 34)
    {
        InsterMonster(0, 0, 1);
        InsterMonster(1, 1, 2);
    }
    else if (counter > 34 && counter <= 35)
    {
        InsterMonster(0, 0, 3);
        InsterMonster(1, 1, 3);
    }
    else if (counter > 35 && counter <= 52)
    {
        InsterMonster(0, 2, 4);
        InsterMonster(0, 0, 4);
        InsterMonster(1, 1, 1);
    }
    if(counter > 52 && counter <= 56)
    {
        InsterMonster(0, 0, 3);
        InsterMonster(1, 1, 3);
    }
    if (counter > 52 && counter <= 71)
    {
        InsterMonster(0, 2, 2);
        InsterMonster(0, 0, 5);
        InsterMonster(1, 3, 1);
        InsterMonster(1, 1, 4);
    }

    if (counter > 71 && MonsterVec.empty())   //时间大于71且怪物数组为空时游戏胜利
        victorylable->show();

    counter++;          //计数器+1
    update();
}

//根据数组画出地图函数
//由绘图函数调用
void MainWindow::DrawMapArr(QPainter& painter)
{
    //地图数组  第一关
    int Map_1[16][26] =
    {
        2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 1, 1, 3, 6, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 1, 1, 6, 6, 2, 2, 2, 2, 2, 2, 3, 6, 1, 1, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 3, 6, 1, 1, 3, 6, 2, 2, 2, 2, 2, 2, 6, 6, 1, 1, 3, 6, 2, 2, 2,
        2, 2, 2, 2, 2, 6, 6, 1, 1, 6, 6, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 2, 2, 2,
        2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2,
        2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 6, 1, 1, 2, 2, 2, 2, 3, 6, 2, 2, 2, 2, 2,
        2, 1, 1, 3, 6, 2, 2, 2, 2, 2, 2, 6, 6, 1, 1, 2, 2, 2, 2, 6, 6, 2, 2, 2, 2, 2,
        2, 1, 1, 6, 6, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 3, 6, 2, 1, 1, 1, 1, 1, 1, 5, 1,
        2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 6, 6, 2, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 1, 1, 2, 3, 6, 2, 2, 2, 2, 3, 6, 2, 1, 1, 2, 3, 6, 1, 1, 3, 6, 2, 2, 2, 2,
        2, 1, 1, 2, 6, 6, 2, 2, 2, 2, 6, 6, 2, 1, 1, 2, 6, 6, 1, 1, 6, 6, 2, 2, 2, 2,
        2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2,
        2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    };
    //第二关
    int Map_2[16][26] =
    {
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 3, 6, 0, 0, 0, 1, 1, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 6, 6, 0, 0, 0, 1, 1, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 3, 6, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 6, 6, 1, 1, 3, 6, 0, 3, 6, 1, 1, 0, 0, 3, 6, 0, 0, 3, 6, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 6, 6, 0, 6, 6, 1, 1, 0, 0, 6, 6, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 6, 0, 0, 0,
        0, 1, 1, 3, 6, 3, 6, 0, 0, 0, 0, 3, 6, 0, 0, 0, 0, 3, 6, 1, 1, 6, 6, 0, 0, 0,
        0, 1, 1, 6, 6, 6, 6, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 6, 6, 1, 1, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 5, 1, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    int Map_3[16][26] =
    {
        4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 3, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 6, 6, 1, 1, 4, 4, 4, 4, 3, 6, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 1, 1, 1, 1, 4, 4, 4, 4, 6, 6, 1, 1, 3, 6, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 3, 6, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 1, 1, 6, 6, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 6, 6, 1, 1, 3, 6, 4, 4, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 1, 1, 1, 1, 1, 6, 6, 4, 4, 4, 4, 3, 6, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4,
        4, 4, 1, 1, 4, 3, 6, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 3, 6, 4,
        4, 4, 1, 1, 4, 6, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 6, 6, 4,
        4, 4, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 3, 6, 4, 4, 4, 4, 4, 1, 1, 4, 4, 4,
        4, 4, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 6, 6, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4,
        4, 4, 4, 3, 6, 4, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4,
        4, 4, 4, 6, 6, 4, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4,
    };

    int Map[16][26];    //用于拷贝不同的关卡数组

    switch (LevelNumber)
    {
    case 0:
        memcpy(Map, Map_1, sizeof(Map));
        break;
    case 1:
        memcpy(Map, Map_2, sizeof(Map));
        break;
    case 2:
        memcpy(Map, Map_3, sizeof(Map));
        break;
    default:
        break;
    }

    for (int j = 0; j < 16; j++)
        for (int i = 0; i < 26; i++)
        {
            switch (Map[j][i])
            {
            case 0:     //背景地面//
                painter.drawPixmap(i * 40, j * 40, 40, 40,
                    QPixmap(":/image/background.png"));
                break;
            case 1:     //路径地面//
                painter.drawPixmap(i * 40, j * 40, 40, 40,
                    QPixmap(":/image/way.png"));
                break;
            case 2:     //路径地面//
                painter.drawPixmap(i * 40, j * 40, 40, 40,
                    QPixmap(":/image/grass.png"));
                break;
            case 3:     //防御塔坑//
                painter.drawPixmap(i * 40, j * 40, 80, 80,
                    QPixmap(":/image/tower_base.png"));
                //防御塔坑坐标初始化塔坑坐标，插入到塔坑对象数组
                TowerPitVec.push_back(new DefenseTowerPit(i * 40, j * 40));
                break;
            case 4:     //路径地面//
                painter.drawPixmap(i * 40, j * 40, 40, 40,
                    QPixmap(":/image/brick.png"));
                break;
            case 5:     //路径坐标//
                painter.drawPixmap(i * 40, j * 40, 40, 40,
                    QPixmap(":/image/way.png"));
                homecoor->x = i * 40;
                homecoor->y = j * 40;
                break;
            }
        }

    painter.drawPixmap(homecoor->x, homecoor->y, 80, 80,
        QPixmap(":/image/destination.png")); //重点坐标
}

//画出选择框
void MainWindow::DrawSelectionBox(QPainter& painter)
{
    //显示选择框
    if (!SelBox->GetDisplay())
        return;

   //画出选择框
    painter.drawPixmap(SelBox->GetX(), SelBox->GetY(), SelBox->GetWidth(), SelBox->GetHeight(),
        QPixmap(SelBox->GetImgPath()));

    //画出子按钮
    SubbutStr *ASubBut = SelBox->GetSelSubBut();    //接收子按钮结构数组
    for (int i = 0; i < 4; i++)
        painter.drawPixmap(ASubBut[i].SubX, ASubBut[i].SubY, ASubBut[i].SubWidth, ASubBut[i].SubHeight,
            QPixmap(ASubBut[i].SubImgPath));

    painter.setPen(QPen(Qt::yellow, 6, Qt::SolidLine));     //设置画笔
    painter.drawRect(QRect(SelBox->GetX() + 95, SelBox->GetY() + 95, 80, 80));
}

//画出防御塔
void MainWindow::DrawDefenseTower(QPainter& painter)
{
    //画出防御塔
    for (auto defei : DefeTowerVec)  //遍历防御塔数组
    {
        //画出底座
        painter.drawPixmap(defei->GetUpLeftX(), defei->GetUpLeftY(), 80, 80, QPixmap(defei->GetBaseImgPath()));

        //画出所有防御塔的攻击范围
        if(DisplayAllRange)
            painter.drawEllipse(QPoint(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40), defei->GetRange(), defei->GetRange());

        //画出所有防御塔子弹
        for (auto bulli : defei->GetBulletVec())
            painter.drawPixmap(bulli->coor.x, bulli->coor.y, defei->GetBulletWidth(), defei->GetBulletHeight(),QPixmap(defei->GetBulletPath()));

        //画出防御塔
        painter.translate(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40);
        painter.rotate(defei->Getturnangle());             //旋转角度
        painter.translate(-(defei->GetUpLeftX() + 40), -(defei->GetUpLeftY() + 40));
        painter.drawPixmap(defei->GetX(), defei->GetY(), defei->GetWidth(), defei->GetHeight(), QPixmap(defei->GetDefImgPath())/*图片路径*/);

        painter.resetTransform();
    }
}

//画出怪物
void MainWindow::DrawMonster(QPainter& painter)
{
    for (auto moni : MonsterVec)
        painter.drawPixmap(moni->GetX(), moni->GetY(), moni->GetWidth(), moni->GetHeight(), QPixmap(moni->GetImgPath()));
}

//防御塔和升级按钮
void MainWindow::DrawRangeAndUpgrade(QPainter& painter)
{
    //防御塔攻击范围和升级按钮
    for (auto defei : DefeTowerVec)
        if(defei->GetUpLeftX() == DisplayRangeX && defei->GetUpLeftY() == DisplayRangeY && DisplayRange)
        {
            painter.setPen(QPen(Qt::white));  //画出范围
            painter.drawEllipse(QPoint(DisplayRangeX + 40, DisplayRangeY + 40), defei->GetRange(), defei->GetRange());
            painter.drawPixmap(DisplayRangeX + 10, DisplayRangeY - 80, 60, 60, QPixmap(":/image/upgrade.png"));
        }
}

//爆炸效果
void MainWindow::DrawExplosion(QPainter& painter)
{
    //显示所有爆炸效果
    for (auto expli : ExploEffectCoor)
            painter.drawPixmap(expli->coor.x - (expli->ExplRangeWidth >> 1), expli->coor.y - (expli->ExplRangeHeight >> 1),
                expli->ExplRangeWidth, expli->ExplRangeHeight, QPixmap(QString(":/image/ExplosionEffect%1.png").arg(expli->index)));
}

//绘图事件
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);     //创建画家类

    painter.setRenderHint(QPainter::Antialiasing);    //设置抗锯齿

    DrawMapArr(painter);        //画出地图

    DrawDefenseTower(painter);  //画出防御塔和子弹

    DrawMonster(painter);       //画出怪物

    DrawRangeAndUpgrade(painter);//画出攻击范围和升级按钮

    DrawExplosion(painter);     //画出爆炸效果

    DrawSelectionBox(painter);  //画出选择框
}


void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() != Qt::LeftButton)
        return;

    //判断升级按钮的点击
    if (DisplayRange)
    {
        if (MouClickRegion(DisplayRangeX + 10, 60 , DisplayRangeY - 80, 60))
        {

            for (auto defei : DefeTowerVec)
                if (defei->GetUpLeftX() == DisplayRangeX && defei->GetUpLeftY() == DisplayRangeY && DisplayRange)
                {
                    if (DeductionMoney(200)) return;        //升级防御塔需要花费200

                    defei->SetAttack(defei->GetAttack() + 20);          //升级攻击力+20
                    defei->SetWidthHeight(defei->GetWidth() + 12, defei->GetHeight() + 6);   //升级表现在尺寸的增加
                    defei->SetXY(defei->GetX() - 6, defei->GetY() - 3); //调整防御塔坐标
                    defei->SetAimsMonster(NULL);
                    defei->SetRange() += 15;                            //设置防御塔的攻击范围
                    defei->SetExplRangeWidthHeight(defei->GetExplRangeWidth() + 5, defei->GetExplRangeHeight() + 5); //设置防御塔攻击怪物所产生的爆炸效果宽高
                    defei->SetBulletWidthHeight(defei->GetBulletWidth() + 5, defei->GetBulletHeight() + 5);          //设置子弹宽高
                    break;
                }

            SelBox->SetDisplay(false);      //取消显示新建防御塔框
            DisplayRange = false;
            update();
            return;
        }
    }

    //判断选择框四个子按钮的点击
    SubbutStr *ASubBut = SelBox->GetSelSubBut();
    for (int i = 0; i < 4; i++)
        if (MouClickRegion(ASubBut[i].SubX, ASubBut[i].SubWidth, ASubBut[i].SubY, ASubBut[i].SubHeight) && SelBox->GetDisplay())
        {
            SelBox->SetDisplay(false);      //取消显示选择框

            //根据点击的不同的按钮，将防御塔子类插入到防御塔父类数组
            switch (i)
            {
            case 0: //board
                if (DeductionMoney(100)) return;
                DefeTowerVec.push_back(new board(SelBox->GetX() + 110, SelBox->GetY() + 112, SelBox->GetX() + 95, SelBox->GetY() + 95, 72, 46));
                break;
            case 1: //fork
                if (DeductionMoney(160)) return;
                DefeTowerVec.push_back(new fork(SelBox->GetX() + 110, SelBox->GetY() + 112, SelBox->GetX() + 95, SelBox->GetY() + 95, 72, 46));
                break;
            case 2: //bell
                if (DeductionMoney(240)) return;
                DefeTowerVec.push_back(new bell(SelBox->GetX() + 110, SelBox->GetY() + 112, SelBox->GetX() + 95, SelBox->GetY() + 95, 76, 50));
                break;
            case 3: //plate
                if (DeductionMoney(400)) return;
                DefeTowerVec.push_back(new plate(SelBox->GetX() + 110, SelBox->GetY() + 104, SelBox->GetX() + 95, SelBox->GetY() + 95, 80, 70));
                break;
            default:
                break;
            }

            update();
            return;
        }

    for (auto APit : TowerPitVec)
        //判断点击塔坑
        if (MouClickRegion(APit->GetX(), APit->GetWidth(), APit->GetY(), APit->GetHeight()))
        {
            DisplayRange = false;
            for (auto defei : DefeTowerVec)      //
                if(defei->GetUpLeftX() == APit->GetX() && defei->GetUpLeftY() == APit->GetY())
                {
                    DisplayRangeX = defei->GetUpLeftX(), DisplayRangeY = defei->GetUpLeftY();   //记录要显示攻击范围的防御塔的坐标
                    DisplayRange = true;        //显示防御塔攻击范围
                    return;
                }

            SelBox->CheckTower(APit->GetX(), APit->GetY());  //选中防御塔，选择框显示
            update();

            return;
        }

    DisplayRange = false;           //取消显示防御塔攻击范围
    SelBox->SetDisplay(false);      //取消显示选择框

    update();
}


//析构释放内存
MainWindow::~MainWindow()
{

    for (auto it = TowerPitVec.begin(); it != TowerPitVec.end(); it++)
    {
        delete *it;
        *it = NULL;
    }
    delete SelBox;
    SelBox = NULL;
    for (auto it = DefeTowerVec.begin(); it != DefeTowerVec.end(); it++)
    {
        delete *it;
        *it = NULL;
    }
    for (auto it = MonsterVec.begin(); it != MonsterVec.end(); it++)
    {
        delete *it;
        *it = NULL;
    }
    for (auto it = ExploEffectCoor.begin(); it != ExploEffectCoor.end(); it++)
    {
        delete *it;
        *it = NULL;
    }

    delete homecoor;
}
