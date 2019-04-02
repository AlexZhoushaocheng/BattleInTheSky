//
// Created by Administrator on 2019/3/31.
//

#include "GameLayer.h"
#include "Resource.h"
#include "GameConfig.h"
#include "Ship.h"
#include "SimpleAudioEngine.h"
#include "Bullet.h"
#include "Enemy.h"

using namespace cocos2d;
using namespace CocosDenshion;

GameLayer::GameLayer() :
        m_pScoreLabel(nullptr),
        m_pShip(nullptr) {

}

bool GameLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    auto winSize = Director::getInstance()->getWinSize();

    //add contact test listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(RES.textureOpaquePack_plist);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(RES.b01_plist);

    WM.SOCRE = 0;
    WM.LIFE = 25;

    // OpaqueBatch
    auto texOpaque = Director::getInstance()->getTextureCache()->addImage(RES.textureOpaquePack_png);
    m_pTexOpaqueBatch = SpriteBatchNode::createWithTexture(texOpaque);
    m_pSparkBatch = SpriteBatchNode::createWithTexture(texOpaque);
    this->addChild(m_pTexOpaqueBatch);
    this->addChild(m_pSparkBatch);

    // TransparentBatch
    auto texTransparent = Director::getInstance()->getTextureCache()->addImage(RES.textureTransparentPack_png);
    m_pTexTransparentBatch = SpriteBatchNode::createWithTexture(texTransparent);
    this->addChild(m_pTexTransparentBatch);

    //score
    m_pScoreLabel = Label::createWithBMFont(RES.arial_14_fnt, "Score: 0");
    m_pScoreLabel->setAnchorPoint(Vec2(1, 0));
    m_pScoreLabel->setPosition(winSize.width - 1, winSize.height - 30);
    m_pScoreLabel->setScale(WM.SCALE);
    m_pScoreLabel->setAlignment(TextHAlignment::RIGHT);
    this->addChild(m_pScoreLabel, 1000);

    //ship life
    auto scale = 0.6;
    auto lifeSprite = Sprite::createWithSpriteFrameName("ship03.png");
    lifeSprite->setScale(scale);
    lifeSprite->setAnchorPoint(Vec2(0, 0.5));
    lifeSprite->setPosition(0, winSize.height - lifeSprite->getContentSize().height * scale / 2 + 15); //15 图片上部的空白 偏移量
    m_pTexTransparentBatch->addChild(lifeSprite, 1, 5);

    //ship life count - life Sprite->getContentSize().height * scale
    m_pLifeCountLabel = Label::createWithTTF("0", RES.arial_ttf, 20);
    m_pLifeCountLabel->setAnchorPoint(Vec2(0, 0.5));
    m_pLifeCountLabel->setPosition(lifeSprite->getPositionX() + lifeSprite->getContentSize().width * scale + 6,
                                   lifeSprite->getPositionY() - 7); //
    m_pLifeCountLabel->setColor(Color3B(255, 0, 0));
    this->addChild(m_pLifeCountLabel, 1000);

    //explosion batch node
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(RES.explosion_plist);
    auto explosionTexture = Director::getInstance()->getTextureCache()->addImage(RES.explosion_png);
    m_pExplosions = SpriteBatchNode::createWithTexture(explosionTexture);
    m_pExplosions->setBlendFunc(BlendFunc::ADDITIVE);
    this->addChild(m_pExplosions);

    if (WM.Sound) {
        SimpleAudioEngine::getInstance()->playBackgroundMusic(
                CC_TARGET_PLATFORM == CC_PLATFORM_WINRT ? RES.bgMusic_wav : RES.bgMusic_mp3, true);
    }

    //Ship
    m_pShip = Ship::createShip();
    m_pTexTransparentBatch->addChild(m_pShip);

    //add enemy
    Enemy::spawnEnemy(6);

    initBackground();
    this->scheduleUpdate();

    //key Press
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(GameLayer::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //touch
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [](Touch* touch, Event* event){ return true;};  //必须有触摸开始的回调，不然程序崩溃
    touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved,this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);

    return true;
}

void GameLayer::moveBackground(float delta) {
    auto moveDis = 16 * delta;
    auto scale = Director::getInstance()->getWinSize().width/m_vGameBG[0]->getContentSize().width;

    for (int i = 0; i < m_vGameBG.size(); i++) {
        m_vGameBG[i]->setPositionY(m_vGameBG[i]->getPositionY() - moveDis);
        if (m_vGameBG[i]->getPositionY() + m_vGameBG[i]->getContentSize().height * scale < 0.0f) {
            if (i == 0) {
                m_vGameBG[i]->setPositionY(m_vGameBG[m_vGameBG.size() - 1]->getPositionY() +
                                           m_vGameBG[m_vGameBG.size() - 1]->getContentSize().height * scale - 2);
            } else {
                m_vGameBG[i]->setPositionY(
                        m_vGameBG[i - 1]->getPositionY() + m_vGameBG[i - 1]->getContentSize().height * scale - 2);
            }
        }
    }
}

void GameLayer::moveFlowThings(float delta) {
    (void)delta;
    auto sprite = getFlowThing();
    sprite->setPosition(random(0.0f, Director::getInstance()->getWinSize().width),
                        Director::getInstance()->getWinSize().height);

    sprite->runAction(MoveBy::create(random(10, 12), Vec2(0, 0 - Director::getInstance()->getWinSize().height -
                                                             sprite->getContentSize().height)));
}

void GameLayer::update(float delta) {
    moveBackground(delta);
    Enemy::reborn();
    updateUI();
}

void GameLayer::initBackground() {
    auto bk = Sprite::createWithSpriteFrameName("bg01.png");
    auto scale = Director::getInstance()->getWinSize().width/bk->getContentSize().width;
    bk->setScale(scale);
    bk->setAnchorPoint(Vec2(0, 0));
    this->addChild(bk, -10);
    m_vGameBG.push_back(bk);

    bk = Sprite::createWithSpriteFrameName("bg01.png");
    bk->setScale(scale);
    bk->setAnchorPoint(Vec2(0, 0));
    bk->setPosition(0, bk->getContentSize().height*scale - 2);
    this->addChild(bk, -10);
    m_vGameBG.push_back(bk);

    moveFlowThings(0);
    this->schedule(CC_CALLBACK_1(GameLayer::moveFlowThings, this), 5, "moveFlowThings");
}

cocos2d::Sprite *GameLayer::getFlowThing() {

    auto changeTexture = [](Sprite *sprite) {
        switch (random(1, 4)) {
            case 1:
                sprite->setTexture(
                        SpriteFrameCache::getInstance()->getSpriteFrameByName("lvl1_map1.png")->getTexture());
                sprite->setTextureRect(
                        SpriteFrameCache::getInstance()->getSpriteFrameByName("lvl1_map1.png")->getRect());
                break;
            case 2:
                sprite->setTexture(
                        SpriteFrameCache::getInstance()->getSpriteFrameByName("lvl1_map2.png")->getTexture());
                sprite->setTextureRect(
                        SpriteFrameCache::getInstance()->getSpriteFrameByName("lvl1_map2.png")->getRect());
                break;
            case 3:
                sprite->setTexture(
                        SpriteFrameCache::getInstance()->getSpriteFrameByName("lvl1_map3.png")->getTexture());
                sprite->setTextureRect(
                        SpriteFrameCache::getInstance()->getSpriteFrameByName("lvl1_map3.png")->getRect());
                break;
            default:
                sprite->setTexture(
                        SpriteFrameCache::getInstance()->getSpriteFrameByName("lvl1_map4.png")->getTexture());
                sprite->setTextureRect(
                        SpriteFrameCache::getInstance()->getSpriteFrameByName("lvl1_map4.png")->getRect());
        }
    };

    for (Sprite *flowTh : m_vFlowThings) {
        if (flowTh->getNumberOfRunningActions() < 1) {
            changeTexture(flowTh);
            return flowTh;
        }
    }
    Sprite *sprite = Sprite::create();
    sprite->setAnchorPoint(Vec2(0.5, 0));
    this->addChild(sprite, -9);
    m_vFlowThings.push_back(sprite);
    changeTexture(sprite);
    return sprite;
}

void GameLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
    //Director::getInstance()->popScene();
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_A:
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            m_pShip->getDirection().left = true;
            break;
        case EventKeyboard::KeyCode::KEY_W:
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            m_pShip->getDirection().up = true;
            break;
        case EventKeyboard::KeyCode::KEY_S:
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            m_pShip->getDirection().down = true;
            break;
        case EventKeyboard::KeyCode::KEY_D:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            m_pShip->getDirection().right = true;
            break;
    }
}

void GameLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_A:
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            m_pShip->getDirection().left = false;
            break;
        case EventKeyboard::KeyCode::KEY_W:
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            m_pShip->getDirection().up = false;
            break;
        case EventKeyboard::KeyCode::KEY_S:
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            m_pShip->getDirection().down = false;
            break;
        case EventKeyboard::KeyCode::KEY_D:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            m_pShip->getDirection().right = false;
            break;
    }
}

bool GameLayer::onContactBegin(cocos2d::PhysicsContact &contact) {

    auto shapeA = contact.getShapeA()->getBody()->getNode();
    auto shapeB = contact.getShapeB()->getBody()->getNode();
    if(shapeA && shapeB)
    {
        //击中敌机
        if (shapeA->getTag() == (int)Config::UNIT_TAG::PLAYER_BULLET && shapeB->getTag() == (int)Config::UNIT_TAG::ENEMY )
        {
            shapeA->setPositionY(Director::getInstance()->getWinSize().height + 10);
            ((Enemy*)shapeB)->onAttacked();
        } else if (shapeB->getTag() == (int) Config::UNIT_TAG::PLAYER_BULLET &&
                   shapeA->getTag() == (int) Config::UNIT_TAG::ENEMY) {
            shapeB->setPositionY(Director::getInstance()->getWinSize().height + 10);
            ((Enemy*)shapeA)->onAttacked();
        }

        //玩家被击中
        if (shapeA->getTag() == (int)Config::UNIT_TAG::ENMEY_BULLET && shapeB->getTag() == (int)Config::UNIT_TAG::PLAYER )
        {
            ((Ship*)shapeB)->onAttacked();
            //shapeB->setVisible(!shapeB->isVisible());
        } else if (shapeB->getTag() == (int) Config::UNIT_TAG::ENMEY_BULLET &&
                   shapeA->getTag() == (int) Config::UNIT_TAG::PLAYER) {
            //shapeA->setVisible(!shapeA->isVisible());
            ((Ship*)shapeA)->onAttacked();
        }

        //敌机和玩家相撞
        if (shapeA->getTag() == (int)Config::UNIT_TAG::ENEMY && shapeB->getTag() == (int)Config::UNIT_TAG::PLAYER )
        {
            //shapeB->setVisible(!shapeB->isVisible());
            //shapeA->setVisible(!shapeA->isVisible());
            ((Enemy*)shapeA)->destroy();
            ((Ship*)shapeB)->onAttacked();
        } else if (shapeB->getTag() == (int) Config::UNIT_TAG::ENEMY &&
                   shapeA->getTag() == (int) Config::UNIT_TAG::PLAYER) {
            ((Ship*)shapeA)->onAttacked();
            ((Enemy*)shapeB)->destroy();
        }
    }
    return false;
}

cocos2d::SpriteBatchNode *GameLayer::m_pTexOpaqueBatch = nullptr;
cocos2d::SpriteBatchNode *GameLayer::m_pSparkBatch = nullptr;
cocos2d::SpriteBatchNode *GameLayer::m_pTexTransparentBatch = nullptr;
cocos2d::SpriteBatchNode *GameLayer::m_pExplosions = nullptr;

bool GameLayer::addEnemy(cocos2d::Sprite *node,int zOrder) {
    if(m_pTexTransparentBatch)
    {
        m_pTexTransparentBatch->addChild(node,zOrder);
        return true;
    } else{
        return false;
    }
}

bool GameLayer::addBullet(cocos2d::Sprite *node, int zOrder) {
    if(m_pTexOpaqueBatch)
    {
        m_pTexOpaqueBatch->addChild(node,zOrder);
        return true;
    } else{
        return false;
    }
}

void GameLayer::updateUI() {
    std::stringstream sStream;
    sStream<<"Score: "<<WM.SOCRE;
    m_pScoreLabel->setString(sStream.str());

    std::stringstream stream;
    stream <<"HP " <<WM.LIFE;
    m_pLifeCountLabel->setString(stream.str());
}

void GameLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {
    m_pShip->setPosition(m_pShip->getPosition() + touch->getDelta());
}


void GameLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) {
//    m_pShip->getDirection().right = false;
//    m_pShip->getDirection().left = false;
//    m_pShip->getDirection().up = false;
//    m_pShip->getDirection().down = false;
}

