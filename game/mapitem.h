#ifndef MAPITEM_H
#define MAPITEM_H
#include <QGraphicsItem>

namespace game {

class mapItem : public QGraphicsPixmapItem
{
public:
  //  mapItem();
    virtual ~mapItem();

//private: for time being public, to be changed
    int posX;
    int posY;

};

} //namepsace game
#endif // MAPITEM_H