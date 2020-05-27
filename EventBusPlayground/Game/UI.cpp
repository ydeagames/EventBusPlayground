#include "pch.h"
#include "UI.h"
#include "Framework/GameEventBus.h"

void UI::On(DeviceDepResEvent& event)
{
	buttonSprite = std::make_unique<DirectX::SpriteBatch>(event.context.GetDR().GetD3DDeviceContext());
	DX::ThrowIfFailed(DirectX::CreateWICTextureFromFile(event.context.GetDR().GetD3DDevice(), L"Resources/button.png", nullptr, buttonTexture.ReleaseAndGetAddressOf()));
}

void UI::On(RenderGameEvent& event)
{
	buttonSprite->Begin();
	buttonSprite->Draw(buttonTexture.Get(), DirectX::SimpleMath::Vector2());
	buttonSprite->End();
}

void UI::On(ClickEvent& event)
{
	if (event.pos.x < 116 && event.pos.y < 54)
	{
		PlayerJumpEvent ev;
		EVENT_BUS.Publish(ev);
	}
}
