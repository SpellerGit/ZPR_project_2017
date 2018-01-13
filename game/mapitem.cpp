#include "mapitem.h"

namespace game {

//mapItem::mapItem()
//{

//}

mapItem::~mapItem()
{
    hitPoints=50;
}

bool mapItem::destroyed()
{
    return true;
}

} //namespace game
