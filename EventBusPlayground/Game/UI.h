#pragma once
#include "Event/GameEvents.h"
#include "MyEvents.h"

class UI : public EventHandler<DeviceDepResEvent>, public EventHandler<RenderGameEvent>, public EventHandler<ClickEvent>
{
private:
	std::unique_ptr<DirectX::SpriteBatch> buttonSprite;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> buttonTexture;
	
public:
	void On(DeviceDepResEvent&) override;
	void On(RenderGameEvent&) override;
	void On(ClickEvent&) override;
};
