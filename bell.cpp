#include "bell.h"

//喇叭防御塔类实现
bell::bell(int x, int y, int BellUpLeftX, int BellUpLeftY, int Bellwidth, int Bellheight)
{

    mx = x;
    my = y;
    BaseImgPath = QString(":/image/GreenBottleBase.png");
    DefImgPath = QString(":/image/bell.png");
    width = Bellwidth;
    height = Bellheight;
    UpLeftX = BellUpLeftX;
    UpLeftY = BellUpLeftY;

    Range = 260;    //射程

    BulletPath = QString(":/image/bellbullet.png");
    bulletwidth = 40;
    bulletheight = 40;           //子弹大小

    attack = 110;    //攻击

    explodeWidth = 75;    //爆炸效果宽高
    explodeHeight = explodeWidth;
}
