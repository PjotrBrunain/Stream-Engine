#include "MiniginPCH.h"
#include "InputManager.h"
#include "Command.h"
#include <SDL.h>


bool StreamEngine::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) 
		{
			return false;
		}
		if (e.type == SDL_KEYDOWN) 
		{
			for (const FlexibleCommand flexiCommand : m_Commands)
			{
				if (!flexiCommand.OnRelease)
				{
					if (flexiCommand.KeyBoardButton == e.key.keysym.sym)
					{
						flexiCommand.pCommand->Execute();
					}
				}
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			for (const FlexibleCommand flexiCommand : m_Commands)
			{
				if (!flexiCommand.OnRelease)
				{
					if (flexiCommand.MouseButton == e.button.button)
					{
						flexiCommand.pCommand->Execute();
					}
				}
			}
		}
		if (e.type == SDL_KEYUP)
		{
			for (const FlexibleCommand flexiCommand : m_Commands)
			{
				if (flexiCommand.OnRelease)
				{
					if (flexiCommand.KeyBoardButton == e.key.keysym.sym)
					{
						flexiCommand.pCommand->Execute();
					}
				}
			}
		}
		if (e.type == SDL_MOUSEBUTTONUP)
		{
			for (const FlexibleCommand flexiCommand : m_Commands)
			{
				if (flexiCommand.OnRelease)
				{
					if (flexiCommand.MouseButton == e.button.button)
					{
						flexiCommand.pCommand->Execute();
					}
				}
			}
		}
	}

	for (int i = 0; i < m_AmountOfPlayers; ++i)
	{
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		const DWORD dwResult = XInputGetState(0, &m_CurrentState);
		if (dwResult == ERROR_SUCCESS)
		{
			if (m_CurrentState.Gamepad.wButtons != m_LastButtons)
			{
				auto buttonLambda = [this](const FlexibleCommand& button)
				{
					if (button.OnRelease)
					{
						if ((m_LastButtons & DWORD(button.ControllerButton)) == DWORD(button.ControllerButton) && !IsPressed(button.ControllerButton))
						{
							if (button.pCommand != nullptr)
							{
								button.pCommand->Execute();
							}
						}
					}
					else
					{
						if (IsPressed(button.ControllerButton))
						{
							if (button.pCommand != nullptr)
							{
								button.pCommand->Execute();
							}
						}
					}
				};

				for (const FlexibleCommand& flexiCommand : m_Commands)
				{
					if (flexiCommand.ControllerId == i)
					{
						buttonLambda(flexiCommand);
					}
				}

				//for (int i = 0; i < m_Commands.size(); ++i)
				//{
				//	buttonLambda(m_Commands[i], m_Commands[i].Button);
				//}
				m_LastButtons = m_CurrentState.Gamepad.wButtons;
			}
		}
	}

	return true;
}

bool StreamEngine::InputManager::IsPressed(const DWORD& button) const
{
	//switch (button)
	//{
	//case ControllerButton::ButtonA:
	//	return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	//case ControllerButton::ButtonB:
	//	return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	//case ControllerButton::ButtonX:
	//	return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	//case ControllerButton::ButtonY:
	//	return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	//case ControllerButton::ButtonStart:
	//	return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_START;
	//case ControllerButton::ButtonBack: 
	//	return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
	//case ControllerButton::ButtonDpadUp: 
	//	return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
	//case ControllerButton::ButtonDpadDown: 
	//	return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
	//case ControllerButton::ButtonDpadLeft: 
	//	return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	//case ControllerButton::ButtonDpadRight: 
	//	return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	//default: return false;
	//}
	return m_CurrentState.Gamepad.wButtons & button;
}

void StreamEngine::InputManager::SetCommand(const FlexibleCommand& command)
{
	m_Commands.push_back(command);
}

void StreamEngine::InputManager::SetAmountOfPlayers(int amountOfPlayers)
{
	m_AmountOfPlayers = amountOfPlayers;
}

void StreamEngine::InputManager::ClearCommands()
{
	m_Commands.clear();
}

int StreamEngine::InputManager::GetAmountOfPlayers() const
{
	return m_AmountOfPlayers;
}

void StreamEngine::InputManager::SetCommands(const std::vector<FlexibleCommand>& commands)
{
	m_Commands = commands;
}

