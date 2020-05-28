#pragma once
#include "Event/EventBus.h"

// クリックイベント
class ClickEvent : public Event
{
public:
	DirectX::SimpleMath::Vector3 pos;
};

// ジャンプイベント
class PlayerJumpEvent : public Event
{
};
