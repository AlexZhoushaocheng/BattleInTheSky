//
// Created by Administrator on 2019/3/31.
//

#ifndef MYMOONWARRIORS_GAMEBG_H
#define MYMOONWARRIORS_GAMEBG_H

#include "cocos2d.h"

class GameBG: public cocos2d::Sprite {
public:
    bool init() override;

    static GameBG* createGameBG();

private:
    bool b_mActive;
};

#endif //MYMOONWARRIORS_GAMEBG_H
