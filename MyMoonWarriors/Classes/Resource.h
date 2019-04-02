//
// Created by Administrator on 2019/3/29.
//

#ifndef MYMOONWARRIORS_RESOURCE_H
#define MYMOONWARRIORS_RESOURCE_H

struct Resource {
    static Resource& getInstance()
    {
        static Resource res;
        return res;
    }
    const char *bgMusic_mp3 = "Music/bgMusic.mp3";
    const char *bgMusic_ogg = "Music/bgMusic.ogg";
    const char *bgMusic_wav = "Music/bgMusic.wav";
    const char *buttonEffect_mp3 = "Music/buttonEffect.mp3";
    const char *buttonEffect_ogg = "Music/buttonEffect.ogg";
    const char *buttonEffect_wav = "Music/buttonEffect.wav";
    const char *explodeEffect_mp3 = "Music/explodeEffect.mp3";
    const char *explodeEffect_ogg = "Music/explodeEffect.ogg";
    const char *explodeEffect_wav = "Music/explodeEffect.wav";
    const char *fireEffect_mp3 = "Music/fireEffect.mp3";         //unused
    const char *fireEffect_ogg = "Music/fireEffect.ogg";         //unused
    const char *fireEffect_wav = "Music/fireEffect.wav";         //unused
    const char *mainMainMusic_mp3 = "Music/mainMainMusic.mp3";
    const char *mainMainMusic_ogg = "Music/mainMainMusic.ogg";
    const char *mainMainMusic_wav = "Music/mainMainMusic.wav";
    const char *shipDestroyEffect_mp3 = "Music/shipDestroyEffect.mp3";
    const char *shipDestroyEffect_ogg = "Music/shipDestroyEffect.ogg";
    const char *shipDestroyEffect_wav = "Music/shipDestroyEffect.wav";
    const char *arial_14_fnt = "arial-14.fnt";
    const char *arial_14_png = "arial-14.png";
    const char *arial_ttf = "fonts/arial.ttf";
    const char *b01_plist = "b01.plist";
    const char *b01_png = "b01.png";
    const char *cocos2d_html5_png = "cocos2d-html5.png";
    const char *explosion_plist = "explosion.plist";
    const char *explosion_png = "explosion.png";
    const char *flare_jpg = "flare.jpg";
    const char *gameOver_png = "gameOver.png";
    const char *gameOverBack_png = "gameoverBack.png";
    const char *level01_tmx = "level01.tmx";
    const char *loading_png = "loading.png";
    const char *logo_png = "logo.png";
    const char *logoBack_png = "logoBack.png";
    const char *menu_png = "menu.png";
    const char *menuTitle_png = "menuTitle.png";
    const char *textureOpaquePack_plist = "textureOpaquePack.plist";
    const char *textureOpaquePack_png = "textureOpaquePack.png";
    const char *textureTransparentPack_plist = "textureTransparentPack.plist";
    const char *textureTransparentPack_png = "textureTransparentPack.png";
    const char *menu_plist = "menu.plist";

private:
    Resource(){}

    virtual ~Resource()final{}
} ;
#define RES Resource::getInstance()
#endif //MYMOONWARRIORS_RESOURCE_H
