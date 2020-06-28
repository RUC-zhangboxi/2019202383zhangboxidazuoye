#ifndef BELL_H
#define BELL_H

#include "weapon.h"
//喇叭类
class bell : public weapon
{
public:
    bell(int x, int y, int FUpLeftX, int FUpLeftY, int Fwidth = 80, int Fheight = 80);
};

#endif // BELL_H
