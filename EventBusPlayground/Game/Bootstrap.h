#pragma once
#include "UI.h"
#include "Controller.h"
#include "Player.h"

// ゲームの開始地点
class Bootstrap
{
private:
	// イベントバスは、あくまでもイベントを管理するものなので
	// オブジェクトのライフサイクルを管理する機能はない
	// オブジェクトの生存にはGameContextなどのライフサイクルの管理機構をうまく活用すること
	std::unique_ptr<UI> ui;
	std::unique_ptr<Controller> controller;
	std::unique_ptr<Player> player;
	
public:
	// 初期化
	void Setup();
};
