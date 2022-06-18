#pragma once

#include <functional>
#include <sstream>

#include "Core/Core.h"

namespace Gem
{
	enum class EventType
	{
		None = 0,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		WindowClosed, WindowFocused, WindowLostFocus, WindowMoved, WindowResized
	};

	enum EventCategory
	{
		// Allows an event to have multiple categories.
		None = 0,
		EventCategoryApplication = (1 << 0),
		EventCategoryInput       = (1 << 1),
		EventCategoryKeyboard    = (1 << 2),
		EventCategoryMouse       = (1 << 3),
		EventCategoryMouseButton = (1 << 4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
	public:
		bool m_Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return (GetCategoryFlags() & category);
		}
	};

	class EventDispatcher
	{
		Event& m_Event;
		template<typename eventType>
		using EventFunc = std::function<bool(eventType&)>;

	public:
		EventDispatcher(Event& event)
			: m_Event(event) { }

		template<typename eventType>
		bool Dispatch(EventFunc<eventType> func)
		{
			if (m_Event.GetEventType() == eventType::GetStaticType())
			{
				m_Event.m_Handled |= func(*(eventType*)&m_Event);
				return true;
			}
			return false;
		}
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}