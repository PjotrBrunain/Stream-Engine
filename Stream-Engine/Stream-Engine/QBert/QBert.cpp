#if _DEBUG
#include <vld.h>
#endif

#include "SDL.h"
#include "Minigin.h"

int main(int, char*[])
{
    StreamEngine::Minigin engine{};
	engine.Run();
	return 0;
}