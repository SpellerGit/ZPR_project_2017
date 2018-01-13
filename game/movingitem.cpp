#include "movingitem.h"
#include <QDebug>

namespace game {

movingItem::movingItem()
{
    speedX =0;
    speedY =0;
    hitPoints=50;
    actions = std::vector<user_action*>();  //maybe add class player to have this, no?
}

movingItem::movingItem(int speedx,
                       int speedy,
                       int posx,
                       int posy)
    : speedX(speedx), speedY(speedy)
{
    setPos(posx,posy);
    hitPoints = 50;
    actions = std::vector<user_action*>();
}

movingItem::movingItem(int speedx,
                       int speedy,
                       int posx,
                       int posy,
                       int hp)
    : speedX(speedx), speedY(speedy)
{
    hitPoints = hp;
    setPos(posx,posy);
    actions = std::vector<user_action*>();

}

void movingItem::accelerate(int accelerate_value)
{
    speedX+=accelerate_value;
}

void movingItem::jump()
{
    speedY=-16; // temporary value
}

void movingItem::move()
{
    if(speedX!=0)
    {
        if(speedX<0)
        speedX=speedX+5;

        if(speedX>0)
        speedX=speedX-5;
    }
    if(speedY<40) //40 - temp value, max velocity
        speedY=speedY+4;
}

bool movingItem::destroyed()
{
    hitPoints -= 10;

    return (hitPoints<=0 ? true : false);
}

void movingItem::setAction(user_action a)
{
    actions.push_back(new user_action(a));
}

void movingItem::releaseAction(user_action a)
{
    //This can be done better i think xd
    //Also using vector in this case is
    //rather not the best. Use list instead?
    bool found = false;
    int j =0;
    for(auto &i : actions)
    {
        if(*i==a)
        {
            found = true;
            break;
        }
        j++;
    }
    if(found)
        actions.erase(actions.begin()+j);

}

} // namespace game
