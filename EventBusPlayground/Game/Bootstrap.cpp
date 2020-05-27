#include "pch.h"
#include "Framework/GameEventBus.h"
#include "Bootstrap.h"

// 初期化コードをここに書く
void Bootstrap::Setup()
{
	ui = std::make_unique<UI>();
	EVENT_BUS.Subscribe<RenderGameEvent>(*ui);
	EVENT_BUS.Subscribe<DeviceDepResEvent>(*ui);
	EVENT_BUS.Subscribe<ClickEvent>(*ui);
	
	controller = std::make_unique<Controller>();
	EVENT_BUS.Subscribe<UpdateGameEvent>(*controller);
	
	player = std::make_unique<Player>();
	EVENT_BUS.Subscribe<DeviceDepResEvent>(*player);
	EVENT_BUS.Subscribe<RenderGameEvent>(*player);
	EVENT_BUS.Subscribe<UpdateGameEvent>(*player);
	EVENT_BUS.Subscribe<PlayerJumpEvent>(*player);
}
