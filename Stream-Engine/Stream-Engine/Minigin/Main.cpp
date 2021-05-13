#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "SDL.h"
#include "Stream-Engine.h"

int main(int, char*[]) {
	StreamEngine::Streamgin engine{};
	engine.Run();
    return 0;
}