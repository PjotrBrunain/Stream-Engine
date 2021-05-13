#if _DEBUG
#include <vld.h>
#endif

#include "SDL.h"
#include "Stream-Engine.h"

int main(int, char*[])
{
    StreamEngine::Streamgin engine{};
	engine.Run();
	return 0;
}
