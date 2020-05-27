#pragma once
#include "Event/EventBus.h"
#include "Event/GameEvents.h"
#include "MyEvents.h"

class Player : public EventHandler<DeviceDepResEvent>, public EventHandler<RenderGameEvent>, public EventHandler<UpdateGameEvent>, public EventHandler<PlayerJumpEvent>
{
private:
	std::unique_ptr<DirectX::SpriteBatch> sprite;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

private:
	DirectX::SimpleMath::Vector2 acc;
	DirectX::SimpleMath::Vector2 pos;

public:
	void On(DeviceDepResEvent& event);
	void On(UpdateGameEvent&) override;
	void On(RenderGameEvent&) override;
	void On(PlayerJumpEvent&) override;
};
