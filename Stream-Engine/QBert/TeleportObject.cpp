#include "TeleportObject.h"

#include <utility>



#include "GameBoardObject.h"
#include "QbertObject.h"
#include "SpriteTextureComponent.h"

void TeleportObject::Activate(std::weak_ptr<QbertObject> pQbertObject, std::weak_ptr<GameBoardObject> pGameBoardObject)
{
	m_IsActivated = true;
	m_pGameBoardObject = std::move(pGameBoardObject);
	m_pQbertObject = std::move(pQbertObject);
	m_pQbertObject.lock()->SetIsTeleporting(true);
	m_pQbertObject.lock()->SetIsVisual(false);
	int row{ 0 };
	int column{ 3 };
	m_DestPos = { m_pGameBoardObject.lock()->GetTilePosition(row, column).x + m_pGameBoardObject.lock()->GetTileWidth(row, column) / 4, m_pGameBoardObject.lock()->GetTilePosition(row, column).y - m_pGameBoardObject.lock()->GetHexSize() + m_pGameBoardObject.lock()->GetTileHeight(row, column) / 4, 1 };
}

void TeleportObject::Update(float deltaTime)
{
	if (m_IsVisual)
	{
		if (m_IsActivated)
		{
			if (m_DestPos.x - m_Delta < m_Transform.GetPosition().x && m_Transform.GetPosition().x < m_DestPos.x + m_Delta && (m_DestPos.y - m_Delta < m_Transform.GetPosition().y && m_Transform.GetPosition().y < m_DestPos.y + m_Delta))
			{
				m_IsVisual = false;
				m_pQbertObject.lock()->SetIsTeleporting(false);
				m_pQbertObject.lock()->SetIsVisual(true);
				m_pQbertObject.lock()->Init(0, 3, m_pGameBoardObject.lock());
			}
			else
			{
				glm::vec3 direction{ m_DestPos - m_Transform.GetPosition() };
				direction = direction / sqrtf(powf(direction.x, 2.f) + powf(direction.y, 2.f) + powf(direction.z, 2.f));
				m_Transform.SetPosition(m_Transform.GetPosition() + direction * deltaTime * m_Speed);
				if (m_RemainingFrameTime <= 0)
				{
					unsigned int srcIdx{ GetComponent<SpriteTextureComponent>()->GetCurrentSrcRectIdx() };
					srcIdx++;
					srcIdx = srcIdx % GetComponent<SpriteTextureComponent>()->GetSrcRectVecLength();
					if (srcIdx == 0)
					{
						srcIdx++;
					}
					GetComponent<SpriteTextureComponent>()->SetSrcRectIdx(srcIdx);
					m_RemainingFrameTime = 60;
				}
				else
				{
					m_RemainingFrameTime -= deltaTime;
				}
			}
		}
	}
}

bool TeleportObject::GetIsActivated() const
{
	return m_IsActivated;
}
