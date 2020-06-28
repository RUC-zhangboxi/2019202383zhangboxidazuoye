#include "fork.h"

//叉子防御塔类函数实现
//构造
fork::fork(int x, int y, int ForkUpLeftX, int ForkUpLeftY, int Forkwidth, int Forkheight)
{

    mx = x;
    my = y;
    BaseImgPath = QString(":/image/FireBottleBase.png");
    DefImgPath = QString(":/image/fork.png");
    width = Forkwidth;
    height = Forkheight;
    UpLeftX = ForkUpLeftX;
    UpLeftY = ForkUpLeftY;

    Range = 170;    //射程

    BulletPath = QString(":/image/forkbullet.png");
    bulletwidth = 40;
    bulletheight = 40;           //子弹大小

    attack = 80;    //攻击力

    explodeWidth = 70;    //爆炸效果宽高
    explodeHeight = explodeWidth;
}
