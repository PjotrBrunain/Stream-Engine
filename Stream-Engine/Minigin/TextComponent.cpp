#include "MiniginPCH.h"
#include "TextComponent.h"

#include <SDL_ttf.h>
#include "Font.h"
#include "GameObject.h"
#include "Texture2D.h"

#include "ResourceManager.h"
#include "Renderer.h"

StreamEngine::TextComponent::TextComponent(std::weak_ptr<GameObject> pOwningGameObject)
	:BaseComponent(true, pOwningGameObject),
	m_pFont(nullptr),
	m_pTexture(nullptr),
	m_Color{ 255,255,255,255 },
	m_pText{ std::make_shared<std::string>("SampleText") },
	m_Size{ 20 },
	m_UpdateText(false),
	m_FontPath()
{
	
}

StreamEngine::TextComponent::TextComponent(const std::string& fontPath, std::weak_ptr<GameObject> pOwningGameObject)
	:TextComponent(pOwningGameObject)
{
	m_FontPath = fontPath;
	m_pFont = ResourceManager::GetInstance().LoadFont(fontPath, m_Size);
	if (m_pFont == nullptr)
	{
		throw std::exception{ "Font failed to initialize" };
	}
	CreateTextTexture();
}

StreamEngine::TextComponent::~TextComponent()
{
}

void StreamEngine::TextComponent::Render() const
{
	Renderer::GetInstance().RenderTexture(*m_pTexture.get(), m_pOwningGameObject.lock()->GetTransform().GetPosition().x, m_pOwningGameObject.lock()->GetTransform().GetPosition().y);
}

void StreamEngine::TextComponent::Update(float deltaTime)
{
	deltaTime = deltaTime;
	if (m_UpdateText)
	{
		CreateTextTexture();
	}
}

void StreamEngine::TextComponent::SetText(const std::string& text)
{
	m_pText = std::make_shared<std::string>(text);
	CreateTextTexture();
}

void StreamEngine::TextComponent::LinkText(const std::shared_ptr<std::string> pText)
{
	m_pText = pText;
	CreateTextTexture();
}

void StreamEngine::TextComponent::SetSize(const int& size)
{
	m_Size = size;
	//CreateTextTexture();
	m_pFont = ResourceManager::GetInstance().LoadFont(m_FontPath, m_Size);
	CreateTextTexture();
}

void StreamEngine::TextComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
	CreateTextTexture();
}

void StreamEngine::TextComponent::SetDoUpdate(bool updateText)
{
	m_UpdateText = updateText;
}

void StreamEngine::TextComponent::CreateTextTexture()
{
	SDL_Surface* pSurface = TTF_RenderText_Blended(m_pFont->GetFont(), m_pText->c_str(), m_Color);
	if (pSurface == nullptr)
	{
		throw std::runtime_error(std::string("Surface failed to initialize: ") + SDL_GetError());
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), pSurface);
	if (pTexture == nullptr)
	{
		throw std::runtime_error(std::string("SDL_Texture from surface failed to initialize: ") + SDL_GetError());
	}

	SDL_FreeSurface(pSurface);
	m_pTexture = std::make_shared<Texture2D>(pTexture);
}
