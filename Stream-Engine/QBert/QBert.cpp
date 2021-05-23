#if _DEBUG
#include <vld.h>
#endif

#include "SDL.h"
#include "Stream-Engine.h"
#include "LoadFunction.h"

int main(int, char*[])
{
    StreamEngine::Streamgin engine{};
	engine.Run(testLoadFunction);
	return 0;
}