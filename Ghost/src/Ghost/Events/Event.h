#pragma once

#include <functional>

#include "Ghost/Debug/Instrumentor.h"
#include "Ghost/Core/Base.h"

namespace Ghost {
	/*  Events in Ghost are currently blocking, i.e., when an event occurs it
		immediately gets dispatched and must  be dealt with with right then and there.
		For the future, a better strategy might be to buffer events in an event bus
		and process them during the "event" part of the update stage
	*/

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowFocusLost, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::type; }\
								virtual EventType GetEventType() const override{ return GetStaticType(); }\
								virtual const char* GetName() const override {return #type;}

	#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event {
		friend class EventDispatcher;
	public:
		bool handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	};

	class EventDispatcher {
	public:
		EventDispatcher(Event& event)
			:m_Event(event) {
		}

		// F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}
}
