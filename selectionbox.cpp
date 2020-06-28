#include "selectionbox.h"

//构造
SelectionBox::SelectionBox(QString Path, int width, int height) :
    mwidth(width), mheight(height), SelecBoxImgPath(Path) {}

int SelectionBox::GetX() const     //获取横坐标
{
    return mx;
}
int SelectionBox::GetY() const     //获取横坐标
{
    return my;
}
int SelectionBox::GetWidth() const //获取宽
{
    return mwidth;
}
int SelectionBox::GetHeight() const //获取高
{
    return mheight;
}

QString SelectionBox::GetImgPath() const    //返回选择框图片路径
{
    return SelecBoxImgPath;
}

//获取显示状态
bool SelectionBox::GetDisplay() const
{
    return display;
}

//设置显示状态
void SelectionBox::SetDisplay(const bool SetPlay)
{
    display = SetPlay;
}

//选中防御塔
void SelectionBox::CheckTower(int x, int y)
{
    //确定选择框的位置
    mx = x - 95;
    my = y - 95;

    //确定子按钮的位置
    SubBut[0].SubX = mx + 106;
    SubBut[0].SubY = my + 14;
    SubBut[0].SubImgPath = QString(":/image/board.png");

    SubBut[1].SubX = mx + 14;
    SubBut[1].SubY = my + 106;
    SubBut[1].SubImgPath = QString(":/image/fork.png");

    SubBut[2].SubX = mx + 202;
    SubBut[2].SubY = my + 106;
    SubBut[2].SubImgPath = QString(":/image/bell.png");

    SubBut[3].SubX = mx + 106;
    SubBut[3].SubY = my + 190;
    SubBut[3].SubImgPath = QString(":/image/plate.png");

    display = true; //显示状态设为真
}

//获取子按钮结构数组
SubbutStr* SelectionBox::GetSelSubBut()
{
    return SubBut;
}
