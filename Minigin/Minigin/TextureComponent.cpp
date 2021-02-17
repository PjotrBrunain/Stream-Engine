#include "MiniginPCH.h"
#include "TextureComponent.h"

StreamEngine::TextureComponent::TextureComponent(const std::string& texturePath)
{
#if _DEBUG
	std::cout << "TextureComp constructed\n";
#endif
}

StreamEngine::TextureComponent::~TextureComponent()
{
#if _DEBUG
	std::cout << "TextureComp destructed\n";
#endif
}
