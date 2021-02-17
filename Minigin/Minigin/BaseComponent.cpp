#include "MiniginPCH.h"
#include "BaseComponent.h"

StreamEngine::BaseComponent::BaseComponent()
{
#if _DEBUG
	std::cout << "BaseComp constructed\n";
#endif
}

StreamEngine::BaseComponent::~BaseComponent()
{
#if _DEBUG
	std::cout << "BaseComp destructed\n";
#endif
}
