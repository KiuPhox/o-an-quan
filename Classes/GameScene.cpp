#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->board = new Board();
    this->addChild(this->board, 0);

    this->turnLabel = Label::createWithTTF("Player Turn", "fonts/Marker Felt.ttf", 32);
    this->turnLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 30));
    this->addChild(this->turnLabel, 1);
    this->updateTurnLabel();

    auto _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

    GameManager::OnTurnChangedCallback = std::bind(&GameScene::updateTurnLabel, this);

    return true;
}

void GameScene::updateTurnLabel() {
    auto gameMode = GameManager::mode;
    auto playerTurn = GameManager::turn;

    if (gameMode == GameManager::GameMode::COMPUTER) {
        turnLabel->setString(playerTurn == GameManager::PlayerTurn::PLAYER1 ? "Player Turn" : "Computer Turn");
    }
    else {
	    turnLabel->setString(playerTurn == GameManager::PlayerTurn::PLAYER1 ? "Player 1 Turn" : "Player 2 Turn");
    }
}

void GameScene::onMouseDown(cocos2d::EventMouse* event) {
    Vec2 pos = event->getLocationInView();
    this->board->onMouseDown(pos);
}
