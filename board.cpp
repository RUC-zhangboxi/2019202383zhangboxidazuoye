#include "board.h"

//板子防御塔类函数实现
//构造
board::board(int x, int y, int BoardUpLeftX, int BoardUpLeftY, int Boardwidth, int Boardheight)
{

    mx = x;
    my = y;
    BaseImgPath = QString(":/image/GreenBottleBase.png");
    DefImgPath = QString(":/image/board.png");
    width = Boardwidth;
    height = Boardheight;
    UpLeftX = BoardUpLeftX;
    UpLeftY = BoardUpLeftY;

    Range = 220;    //射程

    BulletPath = QString(":/image/boardbullet.png");
    bulletwidth = 30; bulletheight = 30;           //子弹大小

    attack = 60;    //攻击力

    explodeWidth = 65;    //爆炸效果宽高
    explodeHeight = explodeWidth;
}
