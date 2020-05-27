// Copyright 2020 YdeaGames
// This software is released under the MIT License
// 
// �����C�x���g�o�X (�����o�X)

#pragma once

#include <unordered_map>
#include <atomic>

namespace EventBusSystem
{
	// ����TypeID
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

	// ����SparseSet
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

	// �C�x���g
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

	// �C�x���g�n���h���[
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

	// �C�x���g�o�X
	class EventBus
	{
	private:
		// �C�x���g���X�i�[
		using EventListener = IEventHandler*;
		// �C�x���g���X�i�[�R���N�V����
		using EventListenerCollection = std::list<EventListener>;
		// �C�x���g���X�i�[�}�b�v
		using EventListenerMap = SparseSet<TypeIds::type_id_t, EventListenerCollection>;

		// ���X�i�[
		EventListenerMap listeners;

	public:
		// ����
		template<typename TEvent>
		void Publish(TEvent& event)
		{
			for (IEventHandler* handler : listeners[TypeIds::type_id<TEvent>()])
				// �������̂��߂�static_cast���g�p���Ă��邪�A�^���S�̂���dynamic_cast���g���Ă�����
				static_cast<EventHandler<TEvent>*>(handler)->On(event);
		}

		// �o�^
		template<typename TEvent>
		void Subscribe(EventHandler<TEvent>& listener)
		{
			// �C�x���g���X�i�[�R���N�V�����ɒǉ�
			listeners[TypeIds::type_id<TEvent>()].push_back(&listener);
		}

		// ����
		template<typename TEvent>
		void Unsubscribe(EventHandler<TEvent>& listener)
		{
			// �C�x���g���X�i�[�R���N�V�����ɒǉ�
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