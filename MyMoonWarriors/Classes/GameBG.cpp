//
// Created by Administrator on 2019/3/31.
//

#include "GameBG.h"
using namespace cocos2d;

bool GameBG::init() {
    if(!Sprite::init())
    {
        return false;
    }

    return true;
}

GameBG *GameBG::createGameBG() {
    auto pGameBG = new(std::nothrow) GameBG();
    if(pGameBG && pGameBG->init())
    {
        return pGameBG;
    } else
    {
        delete pGameBG;
        //pGameBG = nullptr;
        return nullptr;
    }
}
