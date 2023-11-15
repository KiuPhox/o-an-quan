#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "GameObject/Board.h"
#include "GameObject/Stone.h"
#include "GameManager.h"

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameScene);
private:
    Board *board;

    cocos2d::Label* turnLabel;

    void updateTurnLabel();

    void onMouseDown(cocos2d::EventMouse* event);
    void onMouseMove(cocos2d::EventMouse* event);
};

#endif // __GAME_SCENE_H__
