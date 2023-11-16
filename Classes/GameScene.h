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

    void onPlayerMove(int index, bool left);

    CREATE_FUNC(GameScene);
private:
    Board *board;

    cocos2d::network::SIOClient* client;

    cocos2d::Label* turnLabel;

    void updateUI();

    void onMouseDown(cocos2d::EventMouse* event);
    void onMouseMove(cocos2d::EventMouse* event);
};

#endif // __GAME_SCENE_H__
