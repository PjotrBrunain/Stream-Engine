#pragma once
#include <XInput.h>
#include "Singleton.h"

namespace StreamEngine
{
	class Command;

	struct FlexibleCommand
	{
		std::shared_ptr<Command> pCommand{};
		bool OnRelease{};
		DWORD ControllerButton{};
		int ControllerId{};
		uint32_t KeyBoardButton{};
	};
	
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(const DWORD& button) const;
		void SetCommand(const FlexibleCommand& command);
		void SetAmountOfPlayers(int amountOfPlayers);
	private:
		XINPUT_STATE m_CurrentState{};
		std::vector<FlexibleCommand> m_Commands{};
		WORD m_LastButtons{};
		int m_AmountOfPlayers{ 1 };
	};

}
