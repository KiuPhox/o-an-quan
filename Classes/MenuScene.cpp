#include "MenuScene.h"
#include "GameScene.h"
#include "GameManager.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

bool MenuScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    GameManager::init();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bg = Sprite::create("bg.png");
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg, 0);

    auto easyBtn = MenuItemImage::create("easy_button.png", "easy_button.png", CC_CALLBACK_1(MenuScene::menuEasyCallback, this));
    easyBtn->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 120));
    easyBtn->setScale(0.8f);

    auto hardBtn = MenuItemImage::create("hard_button.png", "hard_button.png", CC_CALLBACK_1(MenuScene::menuHardCallback, this));
    hardBtn->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2));
    hardBtn->setScale(0.8f);

    auto playerBtn = MenuItemImage::create("player_button.png", "player_button.png", CC_CALLBACK_1(MenuScene::menuPlayerCallback, this));
    playerBtn->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 120));
    playerBtn->setScale(0.8f);

    auto menu = Menu::create(easyBtn, hardBtn, playerBtn, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}

void MenuScene::menuEasyCallback(Ref* pSender) {
    GameManager::mode = GameManager::COMPUTER;
    GameManager::difficulty = 1;

    auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 255, 255)));
}

void MenuScene::menuHardCallback(Ref* pSender) {
	GameManager::mode = GameManager::COMPUTER;
    GameManager::difficulty = 5;

	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 255, 255)));
}

void MenuScene::menuPlayerCallback(Ref* pSender) {
    GameManager::mode = GameManager::PLAYER;

    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 255, 255)));
}
