#include "pch.h"
#include "UI.h"
#include "Framework/GameEventBus.h"

// CreateDeviceDependentResources()
void UI::On(DeviceDepResEvent& event)
{
	buttonSprite = std::make_unique<DirectX::SpriteBatch>(event.context.GetDR().GetD3DDeviceContext());
	DX::ThrowIfFailed(DirectX::CreateWICTextureFromFile(event.context.GetDR().GetD3DDevice(), L"Resources/button.png", nullptr, buttonTexture.ReleaseAndGetAddressOf()));
}

// Render()
void UI::On(RenderGameEvent& event)
{
	buttonSprite->Begin();
	buttonSprite->Draw(buttonTexture.Get(), pos);
	buttonSprite->End();
}

// Controllerクラスからイベントを飛ばします
void UI::On(ClickEvent& event)
{
	// ボタンの範囲内のクリックだったら
	if (pos.x < event.pos.x && event.pos.x < pos.x + 116 && pos.y < event.pos.y && event.pos.y < pos.y + 54)
	{
		// ボタンを少しずらす
		pos.y += 2.f;
		
		// ######### 穴埋め2-1 #########
		// PlayerJumpEvent イベントを作成
		PlayerJumpEvent ev;
		// イベントを発火
		EVENT_BUS.Publish(ev);
		// ######### 穴埋め2-1 #########
	}
}
