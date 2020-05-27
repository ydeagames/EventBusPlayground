#pragma once
#include "Event/EventBus.h"

class ClickEvent : public Event
{
public:
	DirectX::SimpleMath::Vector3 pos;
};

class PlayerJumpEvent : public Event
{
};
