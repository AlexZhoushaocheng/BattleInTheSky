//
// Created by Administrator on 2019/3/31.
//

#ifndef MYMOONWARRIORS_GAMELAYER_H
#define MYMOONWARRIORS_GAMELAYER_H

#include "cocos2d.h"

class Ship;

class GameLayer: public cocos2d::Layer{
public:
    GameLayer();
    bool init() override;
    CREATE_FUNC(GameLayer);

    void update(float delta)override;
    void onKeyPressed (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)override;
    void onKeyReleased (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)override;

    //bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    bool onContactBegin(cocos2d::PhysicsContact &contact);

    static bool addEnemy(cocos2d::Sprite* node,int zOrder);
    static bool addBullet(cocos2d::Sprite* node,int zOrder);
private:
    void moveBackground(float delta);
    void initBackground();
    void moveFlowThings(float delta);
    cocos2d::Sprite* getFlowThing();
    void updateUI();
private:
    std::vector<cocos2d::Sprite*> m_vFlowThings;        //背景中移动的漂浮物
    std::vector<cocos2d::Sprite*> m_vGameBG;    //背景
    static cocos2d::SpriteBatchNode* m_pTexOpaqueBatch;
    static cocos2d::SpriteBatchNode* m_pSparkBatch;
    static cocos2d::SpriteBatchNode* m_pTexTransparentBatch;
    static cocos2d::SpriteBatchNode* m_pExplosions;
    cocos2d::Label* m_pScoreLabel;
    cocos2d::Label* m_pLifeCountLabel;
    Ship* m_pShip;
    cocos2d::Vec2 BeganPos;
};


#endif //MYMOONWARRIORS_GAMELAYER_H
