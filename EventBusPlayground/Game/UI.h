#pragma once
#include "Event/GameEvents.h"
#include "MyEvents.h"

// UI
class UI
	: public EventHandler<DeviceDepResEvent>
	, public EventHandler<RenderGameEvent>
	, public EventHandler<ClickEvent>
{
private:
	std::unique_ptr<DirectX::SpriteBatch> buttonSprite;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> buttonTexture;
	DirectX::SimpleMath::Vector2 pos;
	
public:
	void On(DeviceDepResEvent&) override;
	void On(RenderGameEvent&) override;
	void On(ClickEvent&) override;
};
