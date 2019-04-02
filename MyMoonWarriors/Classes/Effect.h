//
// Created by Administrator on 2019/3/30.
//

#ifndef MYMOONWARRIORS_EFFECT_H
#define MYMOONWARRIORS_EFFECT_H
#include "cocos2d.h"
#include <functional>

class Effect {
public:
    static void flareEffect(cocos2d::Sprite* sprite,const std::function<void()>& cllBack);

private:
    cocos2d::SpriteBatchNode* m_pTexOpaqueBatch;
};


#endif //MYMOONWARRIORS_EFFECT_H
