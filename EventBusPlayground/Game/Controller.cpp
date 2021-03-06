﻿#include "pch.h"
#include "Framework/GameEventBus.h"
#include "MyEvents.h"
#include "Controller.h"

Controller::Controller()
	: mouse(std::make_unique<DirectX::Mouse>())
	, keyboard(std::make_unique<DirectX::Keyboard>())
{
}

// Controller::Update()
void Controller::On(UpdateGameEvent& event)
{
	mouseTracker.Update(mouse->GetState());
	keyboardTracker.Update(keyboard->GetState());

	// クリックされたら
	if (mouseTracker.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		// カーソルの位置取得
		const auto state = mouseTracker.GetLastState();
		const auto pos = DirectX::SimpleMath::Vector3(float(state.x), float(state.y), 0.f);

		// ######### 穴埋め1-1 #########
		// ClickEvent イベントを作成
		ClickEvent ev;
		// イベントに位置を代入
		ev.pos = pos;
		// イベントを発火
		EVENT_BUS.Publish(ev);
		// ######### 穴埋め1-1 #########
	}
}
