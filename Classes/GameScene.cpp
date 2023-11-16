#include "GameScene.h"
#include "Utils.h"

USING_NS_CC;
using namespace cocos2d::network;

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

    this->player1Label = Label::createWithTTF("Player 1\n", "fonts/Marker Felt.ttf", 32);
    this->player1Label->setPosition(Vec2(100, visibleSize.height - 50));
    this->addChild(this->player1Label, 1);

    this->player2Label = Label::createWithTTF("Player 2\n", "fonts/Marker Felt.ttf", 32);
    this->player2Label->setPosition(Vec2(visibleSize.width - 100, visibleSize.height - 50));
    this->addChild(this->player2Label, 1);

    auto _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

    GameManager::OnUIChangedCallback = std::bind(&GameScene::updateUI, this);

    if (GameManager::mode == GameManager::GameMode::PLAYER) {
        GameManager::OnPlayerMoveCallback = std::bind(&GameScene::onPlayerMove, this, std::placeholders::_1, std::placeholders::_2);

        client = SocketIO::connect("http://127.0.0.1:3000", *this);

        client->on("player", CC_CALLBACK_2(GameScene::onPlayerConneted, this));
        client->on("player-move", CC_CALLBACK_2(GameScene::onOpponentMove, this));
    }
    else {
        this->updateUI();
    }

    return true;
}

void GameScene::updateUI() {
    auto gameMode = GameManager::mode;

    std::string player1Score = std::to_string(GameManager::player1Score);
    std::string player2Score = std::to_string(GameManager::player2Score);

    if (gameMode == GameManager::GameMode::COMPUTER) {
        turnLabel->setString(GameManager::isPlayerTurn() ? "Your Turn" : "Computer Turn");

        player1Label->setString("Player\n" + player1Score);
        player2Label->setString("Computer\n" + player2Score);
    }
    else {
	    turnLabel->setString(GameManager::isPlayerTurn() ? "Your Turn" : "Opponent Turn");

        if (GameManager::playerId == 1) {
			player1Label->setString("You\n" + player1Score);
			player2Label->setString("Opponent\n" + player2Score);
		}
		else {
			player1Label->setString("You\n" + player2Score);
			player2Label->setString("Opponent\n" + player1Score);
		}
    }
}

void GameScene::onMouseDown(cocos2d::EventMouse* event) {
    Vec2 pos = event->getLocationInView();
    if (GameManager::isPlayerTurn()) {
        this->board->onMouseDown(pos);
    }
}

void GameScene::onPlayerConneted(SIOClient* client, const std::string& data) {
    GameManager::playerId = std::stoi(data);

    this->updateUI();
}

void GameScene::onPlayerMove(int index, bool left) {
    std::string data = std::to_string(GameManager::playerId) + "," + std::to_string(index) + "," + std::to_string(left);
    client->emit("player-move", data);
}

void GameScene::onOpponentMove(SIOClient* client, const std::string& data) {
    std::string trueData = data.substr(1, data.size() - 2);
    std::vector<std::string> splitData = Utils::split(trueData, ",");

    int playerId = std::stoi(splitData[0]);
    if (playerId == GameManager::playerId) return;

    int index = std::stoi(splitData[1]);
    bool left = std::stoi(splitData[2]);

    this->board->move(index, left, [this]() {
        this->board->onMoveDone();
    });

}

void GameScene::onConnect(SIOClient* client) {
    CCLOG("onConnect");
}
void GameScene::onMessage(SIOClient* client, const std::string& data) {
    CCLOG("onMessange");
}
void GameScene::onClose(SIOClient* client) {
    CCLOG("onClose");
}
void GameScene::onError(SIOClient* client, const std::string& data) {
    CCLOG("onError");
}
