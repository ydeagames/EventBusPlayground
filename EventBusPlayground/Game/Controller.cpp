#include "pch.h"
#include "Framework/GameEventBus.h"
#include "MyEvents.h"
#include "Controller.h"

Controller::Controller()
	: mouse(std::make_unique<DirectX::Mouse>())
	, keyboard(std::make_unique<DirectX::Keyboard>())
{
}

void Controller::On(UpdateGameEvent& event)
{
	mouseTracker.Update(mouse->GetState());
	keyboardTracker.Update(keyboard->GetState());

	if (mouseTracker.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		const auto state = mouseTracker.GetLastState();
		ClickEvent ev;
		ev.pos = DirectX::SimpleMath::Vector3(float(state.x), float(state.y), 0.f);
		EVENT_BUS.Publish(ev);
	}
}
