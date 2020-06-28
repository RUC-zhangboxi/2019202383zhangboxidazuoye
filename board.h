#ifndef BOARD_H
#define BOARD_H

#include "weapon.h"

//板子类
class board : public weapon
{
public:
    board(int x, int y, int FUpLeftX, int FUpLeftY, int Fwidth = 80, int Fheight = 80);
};

#endif // BOARD_H
