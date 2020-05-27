#pragma once
#include "Event/GameEvents.h"

class Controller : public EventHandler<UpdateGameEvent>
{
	std::unique_ptr<DirectX::Mouse> mouse;
	std::unique_ptr<DirectX::Keyboard> keyboard;
	DirectX::Mouse::ButtonStateTracker mouseTracker;
	DirectX::Keyboard::KeyboardStateTracker keyboardTracker;

public:
	Controller();
	
public:
	void On(UpdateGameEvent&) override;
};
