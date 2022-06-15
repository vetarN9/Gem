#pragma once

#include "Event.h"

namespace Gem
{

	class GEM_API MouseMovedEvent : public Event
	{
		float m_MouseX, m_MouseY;

	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) { }


		inline int GetX() const { return m_MouseX; }
		inline int GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: (x = " << m_MouseX << ", y = " << m_MouseY << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class GEM_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)


	protected:
		int m_Button;

		MouseButtonEvent(int button)
			: m_Button(button) { }
	};

	class GEM_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) { }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: (Button" << m_Button << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class GEM_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) { }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: (Button " << m_Button << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

	class GEM_API MouseScrolledEvent : public Event
	{
		float m_OffsetX, m_OffsetY;

	public:
		MouseScrolledEvent(float offsetX, float offsetY)
			: m_OffsetX(offsetX), m_OffsetY(offsetY) { }


		inline float GetOffsetX() const { return m_OffsetX; }
		inline float GetOffsetY() const { return m_OffsetY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: (x = " << m_OffsetX << ", y = " << m_OffsetY << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

}