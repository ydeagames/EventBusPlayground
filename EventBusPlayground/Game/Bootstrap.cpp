#include "pch.h"
#include "Framework/GameEventBus.h"
#include "Bootstrap.h"

// 初期化コードをここに書く
void Bootstrap::Setup()
{
	// UI
	ui = std::make_unique<UI>();
	EVENT_BUS.Subscribe<RenderGameEvent>(*ui);
	EVENT_BUS.Subscribe<DeviceDepResEvent>(*ui);
	// ######### 穴埋め1-2 #########
	// ClickEventを受信
	EVENT_BUS.Subscribe<ClickEvent>(*ui);
	// ######### 穴埋め1-2 #########

	// 入力コントローラー
	controller = std::make_unique<Controller>();
	EVENT_BUS.Subscribe<UpdateGameEvent>(*controller);

	// プレイヤー
	player = std::make_unique<Player>();
	EVENT_BUS.Subscribe<DeviceDepResEvent>(*player);
	EVENT_BUS.Subscribe<RenderGameEvent>(*player);
	EVENT_BUS.Subscribe<UpdateGameEvent>(*player);
	// ######### 穴埋め2-2 #########
	// PlayerJumpEventを受信
	EVENT_BUS.Subscribe<PlayerJumpEvent>(*player);
	// ######### 穴埋め2-2 #########
}
