#pragma once

namespace Ghost {
	typedef enum class MouseCode : uint16_t {
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define GT_MOUSE_BUTTON_0      ::Ghost::Mouse::Button0
#define GT_MOUSE_BUTTON_1      ::Ghost::Mouse::Button1
#define GT_MOUSE_BUTTON_2      ::Ghost::Mouse::Button2
#define GT_MOUSE_BUTTON_3      ::Ghost::Mouse::Button3
#define GT_MOUSE_BUTTON_4      ::Ghost::Mouse::Button4
#define GT_MOUSE_BUTTON_5      ::Ghost::Mouse::Button5
#define GT_MOUSE_BUTTON_6      ::Ghost::Mouse::Button6
#define GT_MOUSE_BUTTON_7      ::Ghost::Mouse::Button7
#define GT_MOUSE_BUTTON_LAST   ::Ghost::Mouse::ButtonLast
#define GT_MOUSE_BUTTON_LEFT   ::Ghost::Mouse::ButtonLeft
#define GT_MOUSE_BUTTON_RIGHT  ::Ghost::Mouse::ButtonRight
#define GT_MOUSE_BUTTON_MIDDLE ::Ghost::Mouse::ButtonMiddle
