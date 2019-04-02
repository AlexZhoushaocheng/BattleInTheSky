//
// Created by Administrator on 2019/3/31.
//

#ifndef MYMOONWARRIORS_BULLET_H
#define MYMOONWARRIORS_BULLET_H

#include "cocos2d.h"
#include "GameConfig.h"
#include <vector>

class Bullet: public cocos2d::Sprite{
public:
    Bullet();
    static Bullet* createBullet(Config::UNIT_TAG unitTag);
    static Bullet* getOrCreateBullet(Config::UNIT_TAG unitTag);
    //void update(float dt)override;
    void destroy();
private:
    //bool m_bActive;
    int m_iBulletSpeed;
    Config::WEAPON_TYPE m_weaponType;
    Config::ENEMY_ATTACK_MODE attackMode;

    static std::vector<Bullet*> m_vPlayerBullets;
    static std::vector<Bullet*> m_vEnemyBullets;
};


#endif //MYMOONWARRIORS_BULLET_H
