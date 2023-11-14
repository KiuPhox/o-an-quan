/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GameScene.h"

USING_NS_CC;

Scene* Game::createScene()
{
    return Game::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Game::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto sprite = Sprite::create("bg.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);

    this->mouseLabel = Label::createWithTTF("Mouse Position", "fonts/Marker Felt.ttf", 24);
    this->mouseLabel->setPosition(Vec2(100, visibleSize.height - 20));
    this->addChild(this->mouseLabel, 1);

    auto _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseDown = CC_CALLBACK_1(Game::onMouseDown, this);
    _mouseListener->onMouseMove = CC_CALLBACK_1(Game::onMouseMove, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

    return true;
}

void Game::onMouseDown(cocos2d::EventMouse* event) {
    Vec2 pos = event->getLocationInView();

    // Display position
    std::string str = "x: " + std::to_string((int)pos.x) + ", y: " + std::to_string((int)pos.y);
	this->mouseLabel->setString(str);
}

void Game::onMouseMove(cocos2d::EventMouse* event) {
    Vec2 pos = event->getLocationInView();

    // Display position
    std::string str = "x: " + std::to_string((int)pos.x) + ", y: " + std::to_string((int)pos.y);
    this->mouseLabel->setString(str);
}
