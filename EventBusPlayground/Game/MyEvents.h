#pragma once
#include "Event/EventBus.h"

// �N���b�N�C�x���g
class ClickEvent : public Event
{
public:
	DirectX::SimpleMath::Vector3 pos;
};

// �W�����v�C�x���g
class PlayerJumpEvent : public Event
{
};
