#include "weapon.h"

int weapon::GetX() const     //获取横坐标
{
    return mx;
}

int weapon::GetY() const     //获取横坐标
{
    return my;
}

int weapon::GetWidth() const //获取宽
{
    return width;
}

int weapon::GetHeight() const //获取高
{
    return height;
}

int weapon::Getturnangle() const//获取旋转角度
{
    return turnangle;
}

QString weapon::GetBaseImgPath() const  //获取底座图片路径
{
    return BaseImgPath;
}

QString weapon::GetDefImgPath() const   //获取防御塔图片路径
{
    return DefImgPath;
}

int weapon::GetUpLeftX() const     //获取防御塔左上角原横坐标
{
    return UpLeftX;
}

int weapon::GetUpLeftY() const     //获取防御塔左上角原纵坐标
{
    return UpLeftY;
}

void weapon::Setturnangle(int rot)    //设置旋转角度
{
    turnangle = rot;
}

int weapon::GetRange() const           //获取防御塔射程
{
    return Range;
}

Monster* weapon::GetAimsMonster() const //返回当前防御塔的目标怪物
{
    return aimsmon;
}

void weapon::SetAimsMonster(Monster* mon)  //设置当前防御塔的目标怪物
{
    aimsmon = mon;
}

QString weapon::GetBulletPath() const      //返回防御塔子弹图片路径
{
    return BulletPath;
}

QVector<BulletStr*>& weapon::GetBulletVec()//返回子弹数组
{
    return BulletVec;
}

void weapon::newBullet()     //新建子弹函数
{
    counter++;

    if(counter < 7 || !aimsmon)      //计数器到达一定数值且目标怪物不为空时
        return;

    //向子弹数组中插入子弹
    BulletStr *bull = new BulletStr(CoorStr(UpLeftX + 40, UpLeftY + 40));

    bull->coor.x = UpLeftX + 40, bull->coor.y = UpLeftY + 40;

    //计算每一个子弹的路径
    if((!(aimsmon->GetX() - bull->coor.x)))   //除数为0或时不创建子弹
    {
        delete bull;
        bull = NULL;
        goto L1;
    }

    bull->k = (aimsmon->GetY() - bull->coor.y) / (aimsmon->GetX() - bull->coor.x);
    bull->b = aimsmon->GetY() - aimsmon->GetX() * bull->k;

    bull->coor.x = UpLeftX + 40, bull->coor.y = UpLeftY + 40;

    BulletVec.push_back(bull);              //将子弹插入到子弹数组当中

    if(aimsmon->GetX() <= UpLeftX + 40)     //确定子弹的移动方向
        bull->dirflag = true;
    L1:

    counter = 0;    //计数器重置为0

}

void weapon::BulletMove()         //子弹移动函数
{
    //子弹移动
    for(auto bulli : BulletVec)
    {
        const int speed = 24;              //子弹移动速度，每一次刷新画面移动的像素距离，这个值可以随意

        //子弹的移动方向为左则子弹x坐标每次-=，反之+=
        bulli->dirflag ? bulli->coor.x -= speed : bulli->coor.x += speed;

        bulli->coor.y = bulli->k * bulli->coor.x + bulli->b;    //子弹纵坐标改变
    }


}

int weapon::GetBulletWidth() const //获取子弹的宽度
{
    return bulletwidth;
}

int weapon::GetBulletHeight() const//获取子弹的宽度
{
    return bulletheight;
}

int weapon::GetAttack() const      //获取防御塔攻击力
{
    return attack;
}

void weapon::SetAttack(int attack)       //设置防御塔攻击力
{
    this->attack = attack;
}

void weapon::SetWidthHeight(int width, int height)  //设置防御塔宽高
{
    this->width = width, this->height = height;
}

void weapon::SetXY(int x, int y)       //设置坐标
{
    this->mx = x, this->my = y;
}

int& weapon::SetRange()                //设置防御塔的攻击范围
{
    return Range;
}

int weapon::GetExplRangeWidth() const      //获取爆炸效果宽
{
    return explodeWidth;
}

int weapon::GetExplRangeHeight() const     //获取爆炸效果高
{
    return explodeHeight;
}

void weapon::SetExplRangeWidthHeight(int width, int height)     //设置防御塔对应的爆炸效果的宽高
{
    explodeWidth = width;
    explodeHeight = height;
}

void weapon::SetBulletWidthHeight(int width, int height)         //设置子弹宽高
{
    bulletwidth = width;
    bulletheight = height;
}











