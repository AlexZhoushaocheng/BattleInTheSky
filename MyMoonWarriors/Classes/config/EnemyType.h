//
// Created by Administrator on 2019/3/29.
//

#ifndef MYMOONWARRIORS_ENEMYTYPE_H
#define MYMOONWARRIORS_ENEMYTYPE_H

#include <initializer_list>
#include <vector>
#include "GameConfig.h"
struct EnemyType
{
    unsigned char type;
    char* textureName;
    char* bulletType;
    int HP;
    Config::ENEMY_MOVE_TYPE moveType;
    Config::ENEMY_ATTACK_MODE attackMode;
    int scoreValue;

    static const EnemyType(& getEnemyType())[6]{
        static EnemyType s_gEnemyType[6]= {
                {0, "E0.png", "W2.png", 1,  Config::ENEMY_MOVE_TYPE::ATTACK,     Config::ENEMY_ATTACK_MODE::NORMAL,      15},
                {1, "E1.png", "W2.png", 2,  Config::ENEMY_MOVE_TYPE::ATTACK,     Config::ENEMY_ATTACK_MODE::NORMAL,      20},
                {2, "E2.png", "W2.png", 4,  Config::ENEMY_MOVE_TYPE::HORIZONTAL, Config::ENEMY_ATTACK_MODE::TSUIHIKIDAN, 30},
                {3, "E3.png", "W2.png", 6,  Config::ENEMY_MOVE_TYPE::OVERLAP,    Config::ENEMY_ATTACK_MODE::NORMAL,      45},
                {4, "E4.png", "W2.png", 10, Config::ENEMY_MOVE_TYPE::HORIZONTAL, Config::ENEMY_ATTACK_MODE::TSUIHIKIDAN, 60},
                {5, "E5.png", "W2.png", 15, Config::ENEMY_MOVE_TYPE::HORIZONTAL, Config::ENEMY_ATTACK_MODE::NORMAL,      85}
        };
        return s_gEnemyType;
    }

    static const EnemyType& getEnemyType(int type){
        for(const auto& eType:getEnemyType())
        {
            if(type == eType.type)
                return eType;
        }
        return getEnemyType()[0];
    }
};

template <typename T>
struct EnemyTypes {
    std::vector<T> enemyTypes;
    EnemyTypes(std::initializer_list<T> l){
        for(auto type : l)
        {
            enemyTypes.push_back(type);
        }
    }
};


#endif //MYMOONWARRIORS_ENEMYTYPE_H
