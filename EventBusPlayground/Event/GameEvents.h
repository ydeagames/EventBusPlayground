#pragma once
#include "EventBus.h"
#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"

class GameEventContext
{
public:
	virtual DX::DeviceResources& GetDR() = 0;
	virtual DX::StepTimer& GetTimer() = 0;
	
	DirectX::SimpleMath::Vector2 GetSize()
	{
		auto size = GetDR().GetOutputSize();
		return DirectX::SimpleMath::Vector2(float(size.right), float(size.bottom));
	}
};

class GameEvent : public Event
{
public:
	GameEventContext& context;
	
	GameEvent(GameEventContext& context)
		: context(context)
	{
	}
};

// イベント定義マクロ
#define MAKE_GAME_EVENT(name) \
class name : public GameEvent \
{ \
public: \
	name (GameEventContext& context): GameEvent(context) {} \
}

MAKE_GAME_EVENT(RenderGameEvent);		// 描画イベント
MAKE_GAME_EVENT(UpdateGameEvent);		// 更新イベント
MAKE_GAME_EVENT(InitializeGameEvent);	// 初期化イベント
MAKE_GAME_EVENT(FinalizeGameEvent);		// 終了イベント
MAKE_GAME_EVENT(DeviceDepResEvent);		// CreateDeviceDependentResources
MAKE_GAME_EVENT(WindowSizeDepResEvent);	// CreateWindowSizeDependentResources
MAKE_GAME_EVENT(OnActivatedEvent);		// OnActivated
MAKE_GAME_EVENT(OnDeactivatedEvent);	// OnDeactivated
MAKE_GAME_EVENT(OnSuspendingEvent);		// OnSuspending
MAKE_GAME_EVENT(OnResumingEvent);		// OnResuming
