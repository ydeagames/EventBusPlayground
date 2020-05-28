#include "pch.h"
#include "Player.h"

void Player::On(DeviceDepResEvent& event)
{
	sprite = std::make_unique<DirectX::SpriteBatch>(event.context.GetDR().GetD3DDeviceContext());
	DX::ThrowIfFailed(DirectX::CreateWICTextureFromFile(event.context.GetDR().GetD3DDevice(), L"Resources/player.png", nullptr, texture.ReleaseAndGetAddressOf()));

	pos.x = 200;
}

void Player::On(UpdateGameEvent& event)
{
	float bottom = event.context.GetSize().y;
	
	acc.y += .1f;
	pos += acc * float(event.context.GetTimer().GetElapsedSeconds()) * 60.f;

	if (pos.y > bottom - 100)
	{
		acc.y = 0;
		pos.y = bottom - 100;
	}
}

void Player::On(RenderGameEvent&)
{
	sprite->Begin();
	sprite->Draw(texture.Get(), pos);
	sprite->End();
}

// UIクラスからイベントを飛ばします
void Player::On(PlayerJumpEvent&)
{
	acc.y = -5.f;
}
