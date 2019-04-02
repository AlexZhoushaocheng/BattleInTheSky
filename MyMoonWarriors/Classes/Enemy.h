//
// Created by Administrator on 2019/4/1.
//

#ifndef MYMOONWARRIORS_ENEMY_H
#define MYMOONWARRIORS_ENEMY_H

#include "cocos2d.h"
#include "EnemyType.h"

class Enemy:public cocos2d::Sprite {
public:
    Enemy();
    static Enemy* createEnemy(const EnemyType& enemyType);

    static Enemy* getOrCreateEnemy(const EnemyType& enemyType);

    static void spawnEnemy(int maxNum);

    static void reborn();

    void update(float dt)override;
    void shoot(float dt);

    void onAttacked();
    void destroy();
private:
    int m_iHP;
    bool m_bActive;
    Config::ENEMY_MOVE_TYPE m_eMoveType;
    unsigned char m_iEnemyType;
    static std::vector<Enemy*> m_vEnemys;
public:
    Config::ENEMY_MOVE_TYPE getM_eMoveType() const;
};


#endif //MYMOONWARRIORS_ENEMY_H
