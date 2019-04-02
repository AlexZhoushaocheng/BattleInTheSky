//
// Created by Administrator on 2019/3/31.
//

#include "Bullet.h"
using namespace cocos2d;

Bullet::Bullet()
{

}

Bullet *Bullet::createBullet(Config::UNIT_TAG unitTag) {
    Bullet *sprite = new (std::nothrow) Bullet();
    if (sprite)
    {
        auto body = PhysicsBody::createBox(sprite->getContentSize());
        body->setGravityEnable(false);
        if(Config::UNIT_TAG::PLAYER_BULLET ==  unitTag){
            sprite->initWithSpriteFrameName("W1.png");
            body->setVelocity(Vec2(0,WM.BULLET_SPEED.SHIP));
            body->setContactTestBitmask(WM.MASK.TEST_MASK);
        }
        else {
            sprite->initWithSpriteFrameName("W2.png");
            body->setVelocity(Vec2(0,WM.BULLET_SPEED.ENEMY));
            body->setContactTestBitmask(WM.MASK.TEST_MASK);
        }
        sprite->setTag((int)unitTag);
        sprite->autorelease();
        sprite->addComponent(body);
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

Bullet *Bullet::getOrCreateBullet(Config::UNIT_TAG unitTag) {
    if(Config::UNIT_TAG::PLAYER_BULLET ==  unitTag){
        for(Bullet * bullet : m_vPlayerBullets)
        {
            if(bullet->getPositionY() > Director::getInstance()->getWinSize().height)
            {
                return bullet;
            }
        }
        Bullet * bullet1 = createBullet(unitTag);
        m_vPlayerBullets.push_back(bullet1);
        return bullet1;
    } 
	else
	{
        for(Bullet * bullet : m_vEnemyBullets)
        {
            if(bullet->getPositionY() < 0)
            {
                return bullet;
            }
        }
        Bullet * bullet1 = createBullet(unitTag);
        m_vEnemyBullets.push_back(bullet1);
        return bullet1;
    }
}

//void Bullet::update(float dt) {
//    Node::update(dt);
//}

void Bullet::destroy(){

}

std::vector<Bullet*> Bullet::m_vPlayerBullets;
std::vector<Bullet*> Bullet::m_vEnemyBullets;