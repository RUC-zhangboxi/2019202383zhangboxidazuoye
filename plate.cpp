#include "plate.h"

//飞盘防御塔类实现

plate::plate(int x, int y, int PlateUpLeftX, int PlateUpLeftY, int Platewidth, int Plateheight)
{

    mx = x;
    my = y;
    BaseImgPath = QString(":/image/FireBottleBase.png");
    DefImgPath = QString(":/image/plate.png");
    width = Platewidth;
    height = Plateheight;
    UpLeftX = PlateUpLeftX;
    UpLeftY = PlateUpLeftY;

    Range = 230;    //射程

    BulletPath = QString(":/image/platebullet.png");
    bulletwidth = 40;
    bulletheight = 40;           //子弹大小

    attack = 160;    //攻击力

    explodeWidth = 85;    //爆炸效果宽高
    explodeHeight = explodeWidth;
}
