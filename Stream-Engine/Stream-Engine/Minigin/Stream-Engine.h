#pragma once
struct SDL_Window;
namespace StreamEngine
{
	class Streamgin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		float m_MsPerUpdate{ 0.02f };
	};
}