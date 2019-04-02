//
// Created by Administrator on 2019/3/29.
//

#ifndef MYMOONWARRIORS_GAMECONFIG_H
#define MYMOONWARRIORS_GAMECONFIG_H
struct Config{
    static Config & getInstance(){
        static Config instance;
        return instance;
    }
    bool Sound = true;
    // the counter of active enemies
    int ACTIVE_ENEMIES = 0;

    float LOGOY = 350;
    float FLAREY = 445;
    float SCALE = 1.5f;
    int WIDTH = 480;
    int HEIGHT = 720;
    int LIFE = 0;
    int SOCRE = 0;
    struct FontC{
        unsigned char r;
        unsigned char g;
        unsigned char b;
    } FONTCOLOR = {0x1f,0x2d,0x96};
    float menuHeight = 36;
    float menuWidth = 123;

    //attack mode
    enum class ENEMY_ATTACK_MODE{
        NORMAL = 1,
        TSUIHIKIDAN = 2
    };

    enum class WEAPON_TYPE{
         ONE = 1
    };

    //enemy move type
    enum class ENEMY_MOVE_TYPE{
         ATTACK,
        VERTICAL,
        HORIZONTAL,
        OVERLAP,
    };

    // unit tag
    enum class UNIT_TAG{
        ENMEY_BULLET = 900,
        PLAYER_BULLET = 901,
        ENEMY = 1000,
        PLAYER = 1001
    };

    //bullet speed
    struct BULLET_SPEED{
        int  ENEMY = -200;
        int SHIP = 900;
    }BULLET_SPEED;

    // mask
    struct MASK{
        unsigned char SHIP_CATEGORY = 0x01;
        unsigned char EDGE_CATEGORY = 0x02;
        unsigned char BULLET_CATEGORY = 0x04;
        unsigned char ENEMY_CATEGORY = 0x08;
        int TEST_MASK = 0xffffffff;
    }MASK;

private:
    Config(){};
    virtual ~Config()final{};
    //Config(const Config&) = delete;
};

#define WM Config::getInstance()

#endif //MYMOONWARRIORS_GAMECONFIG_H
