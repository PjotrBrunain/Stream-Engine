#include "LivesObject.h"

#include <utility>



#include "QbertObject.h"
#include "SpriteTextureComponent.h"
#include "Structs.h"

LivesObject::LivesObject(std::weak_ptr<QbertObject> pQbertObject)
	:GameObject(),
	m_pQbertObject(std::move(pQbertObject))
{
}

void LivesObject::Init()
{
	std::shared_ptr<SpriteTextureComponent> pSpriteComp{ std::make_shared<SpriteTextureComponent>("Arcade - QBert - General Sprites.png", weak_from_this()) };
	pSpriteComp->AddSrcRect(Rect{ 0,64,16,16 });
	pSpriteComp->SetSrcRectIdx(0);
	AddComponent(pSpriteComp);
}

void LivesObject::Render()
{
	for (int i = 0; i < m_pQbertObject.lock()->GetLives(); ++i)
	{
		GetComponent<SpriteTextureComponent>()->Render();
		m_Transform.SetPosition(m_Transform.GetPosition().x, m_Transform.GetPosition().y + 20, 1);
	}
	m_Transform.SetPosition(m_Transform.GetPosition().x, m_Transform.GetPosition().y - 20.f * float(m_pQbertObject.lock()->GetLives()), 1);
}
