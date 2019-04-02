//
// Created by Administrator on 2019/3/29.
//

#include "SysMenu.h"
#include "RESource.h"
#include "GameConfig.h"
#include "SimpleAudioEngine.h"
#include "Effect.h"
#include "GameLayer.h"

using  namespace cocos2d;
using namespace CocosDenshion;

SysMenu::SysMenu():Scene(),
m_pShip(nullptr)
{

}
cocos2d::Scene *SysMenu::createScene() {
    return create();
}

bool SysMenu::init(){
    if(!Scene::init())
    {
        return  false;
    }

    auto pSpriteFrameCache = SpriteFrameCache::getInstance();
    pSpriteFrameCache->addSpriteFramesWithFile(RES.textureTransparentPack_plist);
    pSpriteFrameCache->addSpriteFramesWithFile(RES.menu_plist);  //add by myself

    auto winSize = Director::getInstance()->getWinSize();

    //
    auto sprite = Sprite::create(RES.loading_png);
    sprite->setAnchorPoint(Vec2(0,0));
    sprite->setScale(winSize.width / sprite->getContentSize().width);
    this->addChild(sprite,0,1);

    //
    auto logo = Sprite::create(RES.logo_png);
    logo->setScale(WM.SCALE);
    logo->setAnchorPoint(Vec2(0,0));
    logo->setPosition((winSize.width - logo->getContentSize().width * WM.SCALE) / 2,WM.LOGOY);
    this->addChild(logo,10,1);

    //
    auto logoBack = Sprite::create(RES.logoBack_png);
    logoBack->setScale(WM.SCALE);
    logoBack->setAnchorPoint(Vec2(0,0));
    logoBack->setPosition(logo->getPosition().x + (logo->getContentSize().width - logoBack->getContentSize().width )* WM.SCALE/2 ,WM.LOGOY + logo->getContentSize().height); //官方demo中坐标x是60，这里改为相对值
    this->addChild(logoBack,9);

    auto newGameNormal = Sprite::createWithSpriteFrameName("menu_01.png");
    auto newGameSelected = Sprite::createWithSpriteFrameName("menu_05.png");
    auto newGameDisabled = Sprite::createWithSpriteFrameName("menu_09.png");

    auto gameSettingsNormal = Sprite::createWithSpriteFrameName("menu_02.png");
    auto gameSettingsSelected = Sprite::createWithSpriteFrameName("menu_06.png");
    auto gameSettingsDisabled = Sprite::createWithSpriteFrameName("menu_10.png");

    auto aboutNormal = Sprite::createWithSpriteFrameName("menu_03.png");
    auto aboutSelected = Sprite::createWithSpriteFrameName("menu_07.png");
    auto aboutDisabled = Sprite::createWithSpriteFrameName("menu_11.png");

    auto flare = Sprite::create(RES.flare_jpg);
    flare->setVisible(false);
    this->addChild(flare,15,10);
    auto newGame = MenuItemSprite::create(newGameNormal,newGameSelected,newGameDisabled,[&,flare](Ref* sender){
        this->onButtonEffect();
        Effect::flareEffect(flare,std::bind(&SysMenu::onNewGame,this));
    });
//
    auto gameSettings = MenuItemSprite::create(gameSettingsNormal,gameSettingsSelected,gameSettingsDisabled,CC_CALLBACK_1(SysMenu::onSetting,this));
    auto about = MenuItemSprite::create(aboutNormal,aboutSelected,aboutDisabled,CC_CALLBACK_1(SysMenu::onAbout,this));
    newGame->setScale(WM.SCALE);
    gameSettings->setScale(WM.SCALE);
    about->setScale(WM.SCALE);
//
    auto menu = Menu::create(newGame,gameSettings,about,nullptr);
    menu->alignItemsVerticallyWithPadding(15);
    this->addChild(menu);
    menu->setPosition(Vec2(winSize.width/2,winSize.height/2 - 140));

    auto label = Label::createWithTTF("Power by Alex Zhou",RES.arial_ttf,21);
    label->setColor(Color3B(WM.FONTCOLOR.r, WM.FONTCOLOR.g, WM.FONTCOLOR.b));
    this->addChild(label);
    label->setPosition(winSize.width/2, 80);

    this->schedule(CC_CALLBACK_1(SysMenu::onUpdate,this),0.1,"onUpdate");

    if(WM.Sound)
    {
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.7);
        SimpleAudioEngine::getInstance()->playBackgroundMusic(CC_TARGET_PLATFORM == CC_PLATFORM_WINRT  ? RES.mainMainMusic_wav : RES.mainMainMusic_mp3, true);
    }

    m_pShip = Sprite::createWithSpriteFrameName("ship03.png");
    this->addChild(m_pShip,1);
    m_pShip->setPosition(random(0.0f,1.0f) * winSize.width, 0);
    m_pShip->runAction(MoveBy::create(2,Vec2(random(0.0f,1.0f) * winSize.width, m_pShip->getPositionY()+ winSize.height + 100)));
    return true;
}

void SysMenu::onButtonEffect() {
    if(WM.Sound)
    {
        SimpleAudioEngine::getInstance()->playEffect(CC_TARGET_PLATFORM == CC_PLATFORM_WINRT  ? RES.buttonEffect_wav : RES.buttonEffect_mp3);
    }
}

void SysMenu::onSetting(Ref* sender) {
    onButtonEffect();
}

void SysMenu::onAbout(Ref* sender) {
    onButtonEffect();
}

void SysMenu::onUpdate(float t) {
    if(this->m_pShip->getPositionY() > 750)
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        this->m_pShip->setPosition(rand_0_1() * visibleSize.width,10);
        m_pShip->runAction(MoveTo::create(random(2,5),Vec2(rand_0_1() * visibleSize.width, m_pShip->getPositionY()+750)));
    }
}

void SysMenu::onNewGame() {
    SimpleAudioEngine::getInstance()->stopAllEffects();
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    auto gameScene = Scene::create();
    if(gameScene && gameScene->initWithPhysics()){
        gameScene->addChild(GameLayer::create());
        Director::getInstance()->replaceScene(TransitionFade::create(1.5,gameScene));
    }
}


