
#ifndef MAPITEM_H
#define MAPITEM_H
#include <QGraphicsItem>

namespace game {

class mapItem : public QGraphicsPixmapItem
{
public:
    virtual ~mapItem();
    virtual bool destroyed();

//private: for time being public, to be changed
    int posX;
    int posY;
    int hitPoints;

};

} //namepsace game
#endif // MAPITEM_H
