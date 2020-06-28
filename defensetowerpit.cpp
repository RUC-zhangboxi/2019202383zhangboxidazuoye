#include "defensetowerpit.h"

//构造
DefenseTowerPit::DefenseTowerPit(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {}

int DefenseTowerPit::GetX() const     //获取横坐标
{
    return x;
}

int DefenseTowerPit::GetY() const     //获取横坐标
{
    return y;
}

int DefenseTowerPit::GetWidth() const //获取宽
{
    return width;
}

int DefenseTowerPit::GetHeight() const //获取高
{
    return height;
}

