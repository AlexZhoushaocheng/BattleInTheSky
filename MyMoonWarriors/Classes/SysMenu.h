//
// Created by Administrator on 2019/3/29.
//

#ifndef MYMOONWARRIORS_SYSMENU_H
#define MYMOONWARRIORS_SYSMENU_H
#include "cocos2d.h"

class SysMenu:public cocos2d::Scene
{
public:
    SysMenu();
    static cocos2d::Scene* createScene();

    virtual bool init() override;

    // implement the "static create()" method manually
    CREATE_FUNC(SysMenu)

private:
    void onButtonEffect();
    void onSetting(Ref* sender);
    void onAbout(Ref* sender);
    void onUpdate(float t);
    void onNewGame();
private:
    cocos2d::Sprite* m_pShip;
};


#endif //MYMOONWARRIORS_SYSMENU_H
