#include "GameScene.h"
#include "Utils.h"
#include "AI/Alpha.h"

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
    this->player1Label->setPosition(Vec2(100, 50));
    this->addChild(this->player1Label, 1);

    this->player2Label = Label::createWithTTF("Player 2\n", "fonts/Marker Felt.ttf", 32);
    this->player2Label->setPosition(Vec2(visibleSize.width - 100, 50));
    this->addChild(this->player2Label, 1);

    this->pauseBtn = MenuItemImage::create("pause_button.png", "pause_button.png", CC_CALLBACK_1(GameScene::onPauseButtonClicked, this));
    this->pauseBtn->setPosition(Vec2(visibleSize.width - 50, visibleSize.height - 50));
    this->pauseBtn->setScale(0.5f);

    this->resumeBtn = MenuItemImage::create("resume_button.png", "resume_button.png", CC_CALLBACK_1(GameScene::onResumeButtonClicked, this));
    this->resumeBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->resumeBtn->setScale(0.8f);
    this->resumeBtn->setVisible(false);

    auto menu = Menu::create(this->pauseBtn, this->resumeBtn, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

    GameManager::OnUIChangedCallback = std::bind(&GameScene::updateUI, this);
    GameManager::OnTurnChangedCallback = std::bind(&GameScene::onTurnChanged, this);

    if (GameManager::mode == GameManager::GameMode::PLAYER) {
        GameManager::OnPlayerMoveCallback = std::bind(&GameScene::onPlayerMove, this, std::placeholders::_1, std::placeholders::_2);

        client = SocketIO::connect("http://127.0.0.1:3000", *this);

        client->on("player", CC_CALLBACK_2(GameScene::onPlayerConneted, this));
        client->on("player-move", CC_CALLBACK_2(GameScene::onOpponentMove, this));
        client->on("pause", CC_CALLBACK_2(GameScene::onPlayerPause, this));
        client->on("resume", CC_CALLBACK_2(GameScene::onPlayerResume, this));
    }
    else {
        this->updateUI();
    }

    return true;
}

void GameScene::onTurnChanged() {
    if (GameManager::mode == GameManager::GameMode::COMPUTER && !GameManager::isPlayerTurn()) {
        State* state = new State(this->board->board, 1, GameManager::player1Score, GameManager::player2Score);
        Alpha* alpha = new Alpha();

        auto move = alpha->minimax_move(state);

        int index = move.first;
        bool clockwise = move.second;

        float randomDelay = Utils::RandomRange(0.5f, 1.0f);

        this->scheduleOnce([this, index, clockwise](float dt) {
            this->board->move(index, clockwise, [this]() {
                this->board->onMoveDone();
            });
        }, randomDelay, "computer_move");
    }
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

void GameScene::pauseGame() {
    this->resumeBtn->setVisible(true);
    this->pauseBtn->setVisible(false);
    this->board->pause();
}

void GameScene::resumeGame() {
	this->resumeBtn->setVisible(false);
	this->pauseBtn->setVisible(true);
    this->board->resume();
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

void GameScene::onPlayerMove(int index, bool clockwise) {
    std::string data = std::to_string(GameManager::playerId) + "," + std::to_string(index) + "," + std::to_string(clockwise);
    client->emit("player-move", data);
}

void GameScene::onOpponentMove(SIOClient* client, const std::string& data) {
    std::string trueData = data.substr(1, data.size() - 2);
    std::vector<std::string> splitData = Utils::split(trueData, ",");

    int playerId = std::stoi(splitData[0]);
    if (playerId == GameManager::playerId) return;

    int index = std::stoi(splitData[1]);
    bool clockwise = std::stoi(splitData[2]);

    this->board->move(index, clockwise, [this]() {
        this->board->onMoveDone();
    });
}

void GameScene::onPlayerPause(SIOClient* client, const std::string& data) {
	this->pauseGame();
}

void GameScene::onPlayerResume(SIOClient* client, const std::string& data) {
	this->resumeGame();
}

void GameScene::onPauseButtonClicked(Ref* pSender) {
    if (GameManager::mode == GameManager::GameMode::PLAYER) {
        this->client->emit("pause", "");
	}

    this->pauseGame();
}

void GameScene::onResumeButtonClicked(Ref* pSender) {
    if (GameManager::mode == GameManager::GameMode::PLAYER) {
        this->client->emit("resume", "");
    }

    this->resumeGame();
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

