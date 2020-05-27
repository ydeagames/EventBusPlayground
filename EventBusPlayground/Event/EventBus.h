// Copyright 2020 YdeaGames
// This software is released under the MIT License
// 
// 高速イベントバス (高速バス)

#pragma once

#include <unordered_map>
#include <atomic>

namespace EventBusSystem
{
	// 高速TypeID
	namespace TypeIds
	{
		using type_id_t = size_t;

		template<typename T>
		struct type_id_family
		{
			static std::atomic<T> identifier;
		};

		template<typename T>
		std::atomic<T> type_id_family<T>::identifier;

		template<typename T>
		type_id_t type_id()
		{
			static const type_id_t value = type_id_family<type_id_t>::identifier++;
			return value;
		}
	}

	// 高速SparseSet
	template<typename K, typename V>
	class SparseSet
	{
	private:
		std::vector<V> data;

	public:
		V& operator[](K pos)
		{
			if (!(pos < data.size()))
				data.resize(pos + 1, V());
			return data[pos];
		}
	};

	// イベント
	class Event
	{
	public:
		virtual ~Event() = default;
	};

	class CancelableEvent : public Event
	{
	public:
		bool canceled;
	};

	// イベントハンドラー
	class IEventHandler
	{
	public:
		virtual ~IEventHandler() = default;
	};

	template<typename TEvent>
	class EventHandler : public IEventHandler
	{
	public:
		virtual void On(TEvent&) = 0;
	};

	// イベントバス
	class EventBus
	{
	private:
		// イベントリスナー
		using EventListener = IEventHandler*;
		// イベントリスナーコレクション
		using EventListenerCollection = std::list<EventListener>;
		// イベントリスナーマップ
		using EventListenerMap = SparseSet<TypeIds::type_id_t, EventListenerCollection>;

		// リスナー
		EventListenerMap listeners;

	public:
		// 発火
		template<typename TEvent>
		void Publish(TEvent& event)
		{
			for (IEventHandler* handler : listeners[TypeIds::type_id<TEvent>()])
				// 高速化のためにstatic_castを使用しているが、型安全のためdynamic_castを使ってもいい
				static_cast<EventHandler<TEvent>*>(handler)->On(event);
		}

		// 登録
		template<typename TEvent>
		void Subscribe(EventHandler<TEvent>& listener)
		{
			// イベントリスナーコレクションに追加
			listeners[TypeIds::type_id<TEvent>()].push_back(&listener);
		}

		// 解除
		template<typename TEvent>
		void Unsubscribe(EventHandler<TEvent>& listener)
		{
			// イベントリスナーコレクションに追加
			listeners[TypeIds::type_id<TEvent>()].remove(&listener);
		}
	};
}

#ifndef DISABLE_USING_EVENT_BUS_FAST
using EventBusSystem::Event;
using EventBusSystem::CancelableEvent;
using EventBusSystem::EventBus;
using EventBusSystem::EventHandler;
#endif