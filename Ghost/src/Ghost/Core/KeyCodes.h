#pragma once

namespace Ghost {
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

#define GT_KEY_SPACE           ::Ghost::Key::Space
#define GT_KEY_APOSTROPHE      ::Ghost::Key::Apostrophe    /* ' */
#define GT_KEY_COMMA           ::Ghost::Key::Comma         /* , */
#define GT_KEY_MINUS           ::Ghost::Key::Minus         /* - */
#define GT_KEY_PERIOD          ::Ghost::Key::Period        /* . */
#define GT_KEY_SLASH           ::Ghost::Key::Slash         /* / */
#define GT_KEY_0               ::Ghost::Key::D0
#define GT_KEY_1               ::Ghost::Key::D1
#define GT_KEY_2               ::Ghost::Key::D2
#define GT_KEY_3               ::Ghost::Key::D3
#define GT_KEY_4               ::Ghost::Key::D4
#define GT_KEY_5               ::Ghost::Key::D5
#define GT_KEY_6               ::Ghost::Key::D6
#define GT_KEY_7               ::Ghost::Key::D7
#define GT_KEY_8               ::Ghost::Key::D8
#define GT_KEY_9               ::Ghost::Key::D9
#define GT_KEY_SEMICOLON       ::Ghost::Key::Semicolon     /* ; */
#define GT_KEY_EQUAL           ::Ghost::Key::Equal         /* = */
#define GT_KEY_A               ::Ghost::Key::A
#define GT_KEY_B               ::Ghost::Key::B
#define GT_KEY_C               ::Ghost::Key::C
#define GT_KEY_D               ::Ghost::Key::D
#define GT_KEY_E               ::Ghost::Key::E
#define GT_KEY_F               ::Ghost::Key::F
#define GT_KEY_G               ::Ghost::Key::G
#define GT_KEY_H               ::Ghost::Key::H
#define GT_KEY_I               ::Ghost::Key::I
#define GT_KEY_J               ::Ghost::Key::J
#define GT_KEY_K               ::Ghost::Key::K
#define GT_KEY_L               ::Ghost::Key::L
#define GT_KEY_M               ::Ghost::Key::M
#define GT_KEY_N               ::Ghost::Key::N
#define GT_KEY_O               ::Ghost::Key::O
#define GT_KEY_P               ::Ghost::Key::P
#define GT_KEY_Q               ::Ghost::Key::Q
#define GT_KEY_R               ::Ghost::Key::R
#define GT_KEY_S               ::Ghost::Key::S
#define GT_KEY_T               ::Ghost::Key::T
#define GT_KEY_U               ::Ghost::Key::U
#define GT_KEY_V               ::Ghost::Key::V
#define GT_KEY_W               ::Ghost::Key::W
#define GT_KEY_X               ::Ghost::Key::X
#define GT_KEY_Y               ::Ghost::Key::Y
#define GT_KEY_Z               ::Ghost::Key::Z
#define GT_KEY_LEFT_BRACKET    ::Ghost::Key::LeftBracket   /* [ */
#define GT_KEY_BACKSLASH       ::Ghost::Key::Backslash     /* \ */
#define GT_KEY_RIGHT_BRACKET   ::Ghost::Key::RightBracket  /* ] */
#define GT_KEY_GRAVE_ACCENT    ::Ghost::Key::GraveAccent   /* ` */
#define GT_KEY_WORLD_1         ::Ghost::Key::World1        /* non-US #1 */
#define GT_KEY_WORLD_2         ::Ghost::Key::World2        /* non-US #2 */

#define GT_KEY_ESCAPE          ::Ghost::Key::Escape
#define GT_KEY_ENTER           ::Ghost::Key::Enter
#define GT_KEY_TAB             ::Ghost::Key::Tab
#define GT_KEY_BACKSPACE       ::Ghost::Key::Backspace
#define GT_KEY_INSERT          ::Ghost::Key::Insert
#define GT_KEY_DELETE          ::Ghost::Key::Delete
#define GT_KEY_RIGHT           ::Ghost::Key::Right
#define GT_KEY_LEFT            ::Ghost::Key::Left
#define GT_KEY_DOWN            ::Ghost::Key::Down
#define GT_KEY_UP              ::Ghost::Key::Up
#define GT_KEY_PAGE_UP         ::Ghost::Key::PageUp
#define GT_KEY_PAGE_DOWN       ::Ghost::Key::PageDown
#define GT_KEY_HOME            ::Ghost::Key::Home
#define GT_KEY_END             ::Ghost::Key::End
#define GT_KEY_CAPS_LOCK       ::Ghost::Key::CapsLock
#define GT_KEY_SCROLL_LOCK     ::Ghost::Key::ScrollLock
#define GT_KEY_NUM_LOCK        ::Ghost::Key::NumLock
#define GT_KEY_PRINT_SCREEN    ::Ghost::Key::PrintScreen
#define GT_KEY_PAUSE           ::Ghost::Key::Pause
#define GT_KEY_F1              ::Ghost::Key::F1
#define GT_KEY_F2              ::Ghost::Key::F2
#define GT_KEY_F3              ::Ghost::Key::F3
#define GT_KEY_F4              ::Ghost::Key::F4
#define GT_KEY_F5              ::Ghost::Key::F5
#define GT_KEY_F6              ::Ghost::Key::F6
#define GT_KEY_F7              ::Ghost::Key::F7
#define GT_KEY_F8              ::Ghost::Key::F8
#define GT_KEY_F9              ::Ghost::Key::F9
#define GT_KEY_F10             ::Ghost::Key::F10
#define GT_KEY_F11             ::Ghost::Key::F11
#define GT_KEY_F12             ::Ghost::Key::F12
#define GT_KEY_F13             ::Ghost::Key::F13
#define GT_KEY_F14             ::Ghost::Key::F14
#define GT_KEY_F15             ::Ghost::Key::F15
#define GT_KEY_F16             ::Ghost::Key::F16
#define GT_KEY_F17             ::Ghost::Key::F17
#define GT_KEY_F18             ::Ghost::Key::F18
#define GT_KEY_F19             ::Ghost::Key::F19
#define GT_KEY_F20             ::Ghost::Key::F20
#define GT_KEY_F21             ::Ghost::Key::F21
#define GT_KEY_F22             ::Ghost::Key::F22
#define GT_KEY_F23             ::Ghost::Key::F23
#define GT_KEY_F24             ::Ghost::Key::F24
#define GT_KEY_F25             ::Ghost::Key::F25

/* Keypad */
#define GT_KEY_KP_0            ::Ghost::Key::KP0
#define GT_KEY_KP_1            ::Ghost::Key::KP1
#define GT_KEY_KP_2            ::Ghost::Key::KP2
#define GT_KEY_KP_3            ::Ghost::Key::KP3
#define GT_KEY_KP_4            ::Ghost::Key::KP4
#define GT_KEY_KP_5            ::Ghost::Key::KP5
#define GT_KEY_KP_6            ::Ghost::Key::KP6
#define GT_KEY_KP_7            ::Ghost::Key::KP7
#define GT_KEY_KP_8            ::Ghost::Key::KP8
#define GT_KEY_KP_9            ::Ghost::Key::KP9
#define GT_KEY_KP_DECIMAL      ::Ghost::Key::KPDecimal
#define GT_KEY_KP_DIVIDE       ::Ghost::Key::KPDivide
#define GT_KEY_KP_MULTIPLY     ::Ghost::Key::KPMultiply
#define GT_KEY_KP_SUBTRACT     ::Ghost::Key::KPSubtract
#define GT_KEY_KP_ADD          ::Ghost::Key::KPAdd
#define GT_KEY_KP_ENTER        ::Ghost::Key::KPEnter
#define GT_KEY_KP_EQUAL        ::Ghost::Key::KPEqual

#define GT_KEY_LEFT_SHIFT      ::Ghost::Key::LeftShift
#define GT_KEY_LEFT_CONTROL    ::Ghost::Key::LeftControl
#define GT_KEY_LEFT_ALT        ::Ghost::Key::LeftAlt
#define GT_KEY_LEFT_SUPER      ::Ghost::Key::LeftSuper
#define GT_KEY_RIGHT_SHIFT     ::Ghost::Key::RightShift
#define GT_KEY_RIGHT_CONTROL   ::Ghost::Key::RightControl
#define GT_KEY_RIGHT_ALT       ::Ghost::Key::RightAlt
#define GT_KEY_RIGHT_SUPER     ::Ghost::Key::RightSuper
#define GT_KEY_MENU            ::Ghost::Key::Menu