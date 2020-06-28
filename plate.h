#ifndef PLATE_H
#define PLATE_H

#include "weapon.h"

//飞盘类
class plate : public weapon
{
public:
    plate(int x, int y, int FUpLeftX, int FUpLeftY, int Fwidth = 80, int Fheight = 80);
};

#endif // PLATE_H
