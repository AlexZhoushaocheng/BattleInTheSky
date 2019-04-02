//
// Created by Administrator on 2019/3/31.
//

#ifndef MYMOONWARRIORS_SHIP_H
#define MYMOONWARRIORS_SHIP_H

#include "cocos2d.h"

class Ship: public cocos2d::Sprite {
public:
    Ship();

    void update(float dt)override;
    void shoot(float dt);
    static Ship* createShip();

    void onAttacked();
private:
    int m_iSpeed;
    int m_iHP;
    struct Direction {
        bool up;
        bool down;
        bool left;
        bool right;
    } direction;

public:
    Direction &getDirection();
};


#endif //MYMOONWARRIORS_SHIP_H
