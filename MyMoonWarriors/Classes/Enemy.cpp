//
// Created by Administrator on 2019/4/1.
//

#include <config/GameConfig.h>
#include "Enemy.h"
#include "GameLayer.h"
#include "Bullet.h"


using namespace cocos2d;
std::vector<Enemy*> Enemy::m_vEnemys;

Enemy::Enemy() : m_bActive(false),
                 m_iEnemyType(0),
                 m_eMoveType(Config::ENEMY_MOVE_TYPE::HORIZONTAL),
                 m_iHP(0) {

}

Enemy *Enemy::createEnemy(const EnemyType &enemyType) {

    auto sprite = new (std::nothrow) Enemy();
    sprite->m_eMoveType = enemyType.moveType;

    if (sprite->initWithSpriteFrameName(enemyType.textureName))
    {
        auto body = PhysicsBody::createBox(sprite->getContentSize(),PhysicsMaterial(0.1f, 1.0f, 0.0f));
        body->setGravityEnable(false);
        body->setContactTestBitmask(WM.MASK.TEST_MASK);
        sprite->addComponent(body);
        sprite->setTag((int)Config::UNIT_TAG::ENEMY);
        sprite->m_iHP = enemyType.HP;
        sprite->autorelease();
        sprite->setAnchorPoint(Vec2(0,0));
        sprite->m_iEnemyType = enemyType.type;
        if(enemyType.moveType != Config::ENEMY_MOVE_TYPE::ATTACK)
        {
            sprite->schedule(CC_CALLBACK_1(Enemy::shoot,sprite),1.5,"EnemyShoot");
        }
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

Enemy *Enemy::getOrCreateEnemy(const EnemyType& enemyType) {
    for(Enemy* enemyShip: m_vEnemys)
    {
        if(enemyShip->m_bActive == false && enemyShip->m_iEnemyType == enemyType.type)
        {
            enemyShip->setVisible(true);
            enemyShip->m_iHP = enemyType.HP;
            if(enemyShip->m_eMoveType != Config::ENEMY_MOVE_TYPE::ATTACK) {
                enemyShip->schedule(CC_CALLBACK_1(Enemy::shoot, enemyShip), 1.5, "EnemyShoot");
            }
            return enemyShip;
        }
    }

    Enemy* enemy = createEnemy(enemyType);
    m_vEnemys.push_back(enemy);

    return enemy;
}

void Enemy::update(float dt) {

}

void Enemy::shoot(float dt) {
    auto bullet_l = Bullet::getOrCreateBullet(Config::UNIT_TAG::ENMEY_BULLET);
    if (bullet_l && !bullet_l->getParent()) {
        if(!GameLayer::addBullet(bullet_l,3000))
        {
            return;
        }
    }
    bullet_l->setPosition(this->getPositionX() + this->getContentSize().width /2 , this->getPositionY() + this->getContentSize().height /2 );
}

Config::ENEMY_MOVE_TYPE Enemy::getM_eMoveType() const {
    return m_eMoveType;
}

void Enemy::onAttacked() {
    m_iHP--;
    if(m_iHP <=0)
    {
        destroy();
    }
}

void Enemy::destroy() {
    this->setVisible(false);
    this->m_bActive = false;
    this->stopAllActions();
    this->unschedule("EnemyShoot");

    WM.SOCRE += EnemyType::getEnemyType(this->m_iEnemyType).scoreValue;
}

void Enemy::spawnEnemy(int maxNum) {

    auto winSize = Director::getInstance()->getWinSize();
    const auto& arr = EnemyType::getEnemyType();
    for(int i=0; i< maxNum; i++)
    {
        auto type = arr[i%6];
        auto enemy = Enemy::getOrCreateEnemy(type);
        GameLayer::addEnemy(enemy,3000);
        enemy->setPosition((winSize.width - enemy->getContentSize().width)/2, winSize.height + 5);
        auto bornPoint = Vec2(winSize.width * rand_0_1(), winSize.height - enemy->getContentSize().height);
        auto moveBron = MoveTo::create(0.5,bornPoint);
        enemy->runAction(moveBron);
        switch (type.moveType)
        {
            case Config::ENEMY_MOVE_TYPE::ATTACK:
            {

            }
                break;
            default:
            {
                auto move1 = MoveTo::create(winSize.width /450 + 2 * rand_0_1(),Vec2(winSize.width - enemy->getContentSize().width, bornPoint.y));
                auto move2 = MoveTo::create(winSize.width /450 + 2 * rand_0_1(),Vec2(0,bornPoint.y));
                auto move = Sequence::create(move1,move2,nullptr);
                enemy->runAction(RepeatForever::create(move));
            }
        }
    }
}

void Enemy::reborn() {
    auto winSize = Director::getInstance()->getWinSize();
    for(Enemy* enemy : m_vEnemys)
    {
        if(!enemy->m_bActive)
        {
            enemy->setPosition((winSize.width - enemy->getContentSize().width)/2, winSize.height + 5);
            enemy->m_bActive = true;
            enemy->setVisible(true);
            if(enemy->m_eMoveType != Config::ENEMY_MOVE_TYPE::ATTACK){
                enemy->schedule(CC_CALLBACK_1(Enemy::shoot,enemy),1.5,"EnemyShoot");
            }
            enemy->m_iHP = EnemyType::getEnemyType(enemy->m_iEnemyType).HP;

            auto bornPoint = Vec2(winSize.width * rand_0_1(), winSize.height - enemy->getContentSize().height - random(30,70));
            auto moveBron = MoveTo::create(0.5,bornPoint);
//DelayTime::create(2)
            enemy->runAction(Sequence::create(DelayTime::create(1),moveBron,nullptr));

            switch (EnemyType::getEnemyType(enemy->m_iEnemyType).moveType)
            {
                case Config::ENEMY_MOVE_TYPE::ATTACK:
                {
                    auto parent = enemy->getParent();
                    if(!parent)
                        break;
                    auto player = parent->getChildByTag((int)Config::UNIT_TAG::PLAYER);
                    if(!player)
                        break;
                    auto move = MoveTo::create(4,player->getPosition());
                    auto destroy = CallFunc::create([&,enemy](){enemy->destroy();});
                    auto seq = Sequence::create(DelayTime::create(1.5),move,destroy,nullptr);
                    enemy->runAction(seq);
                }
                    break;
                default:
                {
                    auto move1 = MoveTo::create(winSize.width /450+ 2 * rand_0_1(),Vec2(winSize.width - enemy->getContentSize().width, bornPoint.y));
                    auto move2 = MoveTo::create(winSize.width /450+ 2 * rand_0_1(),Vec2(0,bornPoint.y));
                    auto move = Sequence::create(move1,move2,nullptr);
                    enemy->runAction(RepeatForever::create(move));
                }
            }
        }
    }

}


