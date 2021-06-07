#pragma once
#include <SDL_stdinc.h>
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
		Sint32 KeyBoardButton{};
		UINT8 MouseButton{};
	};
	
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(const DWORD& button) const;
		void SetCommand(const FlexibleCommand& command);
		void SetAmountOfPlayers(int amountOfPlayers);
		void ClearCommands();
		int GetAmountOfPlayers() const;

		void SetCommands(const std::vector<FlexibleCommand>& commands);
	private:
		XINPUT_STATE m_CurrentState{};
		std::vector<FlexibleCommand> m_Commands{};
		WORD m_LastButtons{};
		int m_AmountOfPlayers{ 1 };
	};

}
