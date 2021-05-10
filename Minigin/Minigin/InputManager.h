#pragma once
#include <XInput.h>
#include "Singleton.h"

namespace StreamEngine
{
	class Command;
	
	enum class ControllerButton
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
		ButtonStart = XINPUT_GAMEPAD_START,
		ButtonBack = XINPUT_GAMEPAD_BACK,
		ButtonDpadUp = XINPUT_GAMEPAD_DPAD_UP,
		ButtonDpadDown = XINPUT_GAMEPAD_DPAD_DOWN,
		ButtonDpadLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		ButtonDpadRight = XINPUT_GAMEPAD_DPAD_RIGHT
	};

	struct FlexibleCommand
	{
		std::shared_ptr<Command> pCommand;
		bool OnRelease;
		ControllerButton Button;
	};
	
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
		void SetCommand(const FlexibleCommand& command);
	private:
		XINPUT_STATE m_CurrentState{};
		std::vector<FlexibleCommand> m_Commands{};
		WORD m_LastButtons{};
	};

}
