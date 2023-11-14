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

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bg = Sprite::create("bg.png");
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg, 0);

    auto computerBtn = MenuItemImage::create("computer_button.png", "computer_button.png", CC_CALLBACK_1(MenuScene::menuComputerCallback, this));
    computerBtn->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 60));
    computerBtn->setScale(0.8f);

    auto playerBtn = MenuItemImage::create("player_button.png", "player_button.png", CC_CALLBACK_1(MenuScene::menuPlayerCallback, this));
    playerBtn->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 60));
    playerBtn->setScale(0.8f);

    auto menu = Menu::create(computerBtn, playerBtn, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}

void MenuScene::menuComputerCallback(Ref* pSender) {
    GameManager::mode = GameManager::COMPUTER;

    auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 255, 255)));
}

void MenuScene::menuPlayerCallback(Ref* pSender) {
    GameManager::mode = GameManager::PLAYER;

    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 255, 255)));
}
