#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "GameObject/Board.h"
#include "GameObject/Stone.h"
#include "GameManager.h"

#include "cocos2d.h"
#include "network/SocketIO.h"

class GameScene : public cocos2d::Scene, public cocos2d::network::SocketIO::SIODelegate
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    virtual void onConnect(cocos2d::network::SIOClient* client);
    virtual void onMessage(cocos2d::network::SIOClient* client, const std::string& data);
    virtual void onClose(cocos2d::network::SIOClient* client);
    virtual void onError(cocos2d::network::SIOClient* client, const std::string& data);

    void onPlayerConneted(cocos2d::network::SIOClient* client, const std::string& data);
    void onOpponentMove(cocos2d::network::SIOClient* client, const std::string& data);
    void onPlayerPause(cocos2d::network::SIOClient* client, const std::string& data);
    void onPlayerResume(cocos2d::network::SIOClient* client, const std::string& data);

    void onPlayerMove(int index, bool left);

    void onPauseButtonClicked(cocos2d::Ref* pSender);
    void onResumeButtonClicked(cocos2d::Ref* pSender);

    CREATE_FUNC(GameScene);
private:
    Board *board;

    cocos2d::network::SIOClient* client;

    cocos2d::Label* turnLabel;
    cocos2d::Label* player1Label;
    cocos2d::Label* player2Label;

    cocos2d::MenuItemImage *pauseBtn;
    cocos2d::MenuItemImage *resumeBtn;

    void updateUI();
    void pauseGame();
    void resumeGame();

    void onMouseDown(cocos2d::EventMouse* event);
    void onMouseMove(cocos2d::EventMouse* event);
};

#endif // __GAME_SCENE_H__
