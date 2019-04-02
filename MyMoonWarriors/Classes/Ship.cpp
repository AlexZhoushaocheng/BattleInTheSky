//
// Created by Administrator on 2019/3/31.
//

#include "Ship.h"
#include "Bullet.h"
#include "GameLayer.h"

using namespace cocos2d;

Ship::Ship():
        m_iSpeed(220),
        m_iHP(100),
        direction({false,false,false,false})
        {
}


Ship *Ship::createShip() {

    auto sprite = new (std::nothrow) Ship();
    if (sprite  && sprite->initWithSpriteFrameName("ship01.png"))
    {
        auto body = PhysicsBody::createBox(sprite->getContentSize(),PhysicsMaterial(0.1f, 1.0f, 0.0f));
        body->setGravityEnable(false);
        body->setContactTestBitmask(WM.MASK.TEST_MASK);
        sprite->addComponent(body);

        sprite->autorelease();
        sprite->setAnchorPoint(Vec2(0,0));
        Vector<SpriteFrame*> animFrames;
        animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("ship01.png"));
        animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("ship02.png"));
        auto ani = Animation::createWithSpriteFrames(animFrames,0.1);
        Animate* animate = Animate::create(ani);
        sprite->runAction(RepeatForever::create(animate));
        sprite->scheduleUpdate();
        sprite->schedule(CC_CALLBACK_1(Ship::shoot,sprite),1.0f/5,"shoot");
        sprite->setTag((int)Config::UNIT_TAG::PLAYER);
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Ship::update(float dt) {
    auto winSize = Director::getInstance()->getWinSize();
    if(direction.left && this->getPositionX()>0)
    {
        this->setPositionX(this->getPositionX() - dt * m_iSpeed);
    }
    if(direction.right && getPositionX()+ getContentSize().width < winSize.width)
    {
        this->setPositionX(this->getPositionX() + dt * m_iSpeed);
    }
    if(direction.up && getPositionY()+ getContentSize().height < winSize.height)
    {
        this->setPositionY(this->getPositionY() + dt * m_iSpeed);
    }
    if(direction.down && this->getPositionY()>0)
    {
        this->setPositionY(this->getPositionY() - dt * m_iSpeed);
    }
}

Ship::Direction &Ship::getDirection(){
    return direction;
}

void Ship::shoot(float dt) {
    auto bullet_l = Bullet::getOrCreateBullet(Config::UNIT_TAG::PLAYER_BULLET);
	if (bullet_l && !bullet_l->getParent()) {
		//m_pTexOpaqueBatch->addChild(bullet_l, 3000);
		if(!GameLayer::addBullet(bullet_l,3000))
        {
            return;
        }
	}
	bullet_l->setPosition(this->getPositionX() + this->getContentSize().width / 4, this->getPositionY() + 45);

	auto bullet_r = Bullet::getOrCreateBullet(Config::UNIT_TAG::PLAYER_BULLET);
	if (bullet_r && !bullet_r->getParent())
	{
        if(!GameLayer::addBullet(bullet_r,3000))
        {
            return;
        }
		//m_pTexOpaqueBatch->addChild(bullet_r, 3000);
	}
	bullet_r->setPosition(this->getPositionX() + this->getContentSize().width - this->getContentSize().width / 4, this->getPositionY() + 45);
    
}

void Ship::onAttacked() {
    WM.LIFE--;
}
