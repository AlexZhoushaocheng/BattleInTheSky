//
// Created by Administrator on 2019/3/30.
//

#include "Effect.h"
#include "GameConfig.h"


void Effect::flareEffect(cocos2d::Sprite *sprite, const std::function<void()> &onFinishedCllBack) {
    sprite->stopAllActions();
    sprite->setBlendFunc(cocos2d::BlendFunc::ADDITIVE); /** Enables Additive blending. Uses {GL_SRC_ALPHA, GL_ONE} */
    sprite->setPosition(-45,WM.FLAREY);
    sprite->setVisible(true);
    sprite->setOpacity(0);
    sprite->setRotation(-120);
    sprite->setScale(0.3);

    auto opacityAnim = cocos2d::FadeTo::create(0.5,255);
    auto opacDim = cocos2d::FadeTo::create(1,0);
    auto biggerEase = cocos2d::EaseSineOut::create(cocos2d::ScaleBy::create(0.7,1.2));
    auto easeMove = cocos2d::EaseSineOut::create(cocos2d::MoveBy::create(0.5,cocos2d::Vec2(490,0)));
    auto rotateEase = cocos2d::EaseExponentialOut::create(cocos2d::RotateBy::create(2.5,90));
    auto bigger = cocos2d::ScaleTo::create(0.5,1);

    sprite->runAction(cocos2d::Sequence::create(opacityAnim,
                                                biggerEase,
                                                opacDim,
                                                cocos2d::CallFunc::create(onFinishedCllBack),
                                                nullptr));
    sprite->runAction(easeMove);
    sprite->runAction(rotateEase);
    sprite->runAction(bigger);
}
