#include "player.h"
#include "define.h"

int player::move(int direction, float *pos,float *move)
{
    if (pos != nullptr)
    {
        if (direction == LEFT)
        {
            return *pos -= *move;
        }
        if (direction == RIGHT)
        {
            return *pos += *move;
        }
    }
    return 0;
}

void player::update()
{
    posX = 100;
    posY = 700;
    return;
}

void player::uraUpdate()
{
    posX = 388;
    posY = 560;
    return;
}

void player::gravityUpdate()
{
    speed = 0;
    t = 1;
    velY = 0.1;
    return;
}
