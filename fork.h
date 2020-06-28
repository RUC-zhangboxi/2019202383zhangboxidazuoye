#ifndef FORK_H
#define FORK_H

#include "weapon.h"

//叉子类
class fork : public weapon
{
public:
    fork(int x, int y, int FUpLeftX, int FUpLeftY, int Fwidth = 80, int Fheight = 80);
};

#endif // FORK_H
