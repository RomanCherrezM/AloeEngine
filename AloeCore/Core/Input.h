#pragma once

// ALOE-TODO: This should be platform specific -> Platform/Windows/Input/InputKeys/h, 
// and the general file Input.h should be at Platform/Input.h

#include <Core/PlatformTypes.h>

#include <Core/InputProviderBase.h>

#include <string>
#include <memory>

namespace Aloe::Input
{
	std::shared_ptr<InputProvider> CreateGamepadInputProvider();

	enum Key
	{
		Invalid = 0,

#pragma region KeyboardKeys

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

		// For iteration purposes
		FirstKeyboardKey = A, 
		LastKeyboardKey = Z,

#pragma endregion

#pragma region MouseKeys
		// Mouse
		MouseLeftClic,
		MouseRightClic,
		MouseMiddleClic,

		MouseScroll,

		MouseX,
		MouseY,

#pragma endregion

#pragma region GamepadKeys
		// Gamepad

		// ALOE-TODO: Add GamepadLeftThumbstickLeft, Right, Up, Down for virtual directions
		GamepadDPadLeft,
		GamepadDPadRight,
		GamepadDPadUp,
		GamepadDPadDown,

		GamepadFaceLeft,
		GamepadFaceRight,
		GamepadFaceUp,
		GamepadFaceDown,

		GamepadLeftThumbstickX,
		GamepadLeftThumbstickY,
		GamepadRightThumbstickX,
		GamepadRightThumbstickY,

		GamepadLeftThumbstick,
		GamepadRightThumbstick,

		GamepadLeftShoulder,
		GamepadLeftTrigger,
		GamepadRightShoulder,
		GamepadRightTrigger,
#pragma endregion

	};

	// Only for keyboard keys, translates the keycode
	Key TranslateKey(u16 key);
	Key TranslateMouseButton(u16 key);
	Key TranslateGamepadButton(u16 key);
	Key TranslateGamepadAxis(u16 key);

	// To get the display name for the Keys, for now until localization
	const char* GetKeyName(Key key);

	enum InputType
	{
		Pressed,
		Held,
		Released,
	};

	struct InputKeyModifier
	{
		bool m_affecsInput = false; // False meaning this key doesnt have any modifiers

		bool m_alt = false;
		bool m_ctrl = false;
		bool m_shift = false;
		bool m_cmd = false;
	};

	struct InputActionBinding
	{
		std::string m_name; // ALOE-TODO: Hash this
		InputType m_inputType;
		std::function<void()> m_binding;
	};

	struct InputAxisBinding
	{
		std::string m_name; // ALOE-TODO: Hash this
		std::function<void(const float&)> m_binding;
	};
    
}