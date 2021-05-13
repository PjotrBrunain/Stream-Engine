#include "MiniginPCH.h"
#include "InputManager.h"
#include "Command.h"
#include <SDL.h>


bool StreamEngine::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}

	
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	const DWORD dwResult = XInputGetState(0, &m_CurrentState);
	if (dwResult == ERROR_SUCCESS)
	{
		if (m_CurrentState.Gamepad.wButtons != m_LastButtons)
		{
			auto buttonLambda = [this](const FlexibleCommand& button, const ControllerButton& controllerButton)
			{
				if (button.OnRelease)
				{
					if ((m_LastButtons & DWORD(controllerButton)) == DWORD(controllerButton) && !IsPressed(controllerButton))
					{
						if (button.pCommand != nullptr)
						{
							button.pCommand->Execute();
						}
					}
				}
				else
				{
					if (IsPressed(controllerButton))
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
				buttonLambda(flexiCommand, flexiCommand.Button);
			}
			
			//for (int i = 0; i < m_Commands.size(); ++i)
			//{
			//	buttonLambda(m_Commands[i], m_Commands[i].Button);
			//}
			m_LastButtons = m_CurrentState.Gamepad.wButtons;
		}
	}

	return true;
}

bool StreamEngine::InputManager::IsPressed(ControllerButton button) const
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
	return m_CurrentState.Gamepad.wButtons & DWORD(button);
}

void StreamEngine::InputManager::SetCommand(const FlexibleCommand& command)
{
	m_Commands.push_back(command);
}

