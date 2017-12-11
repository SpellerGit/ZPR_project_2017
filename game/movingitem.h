#ifndef MOVINGITEM_H
#define MOVINGITEM_H

#include "game/mapitem.h"

namespace game{

class movingItem : public mapItem
{
public:
    movingItem();
    accelerate(int x);
    jump();

private:
    int speedX;
    int speedY;
};

} // namespcae game

#endif // MOVINGITEM_H
