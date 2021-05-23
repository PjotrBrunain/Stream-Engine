#pragma once
#include "BaseComponent.h"

namespace StreamEngine
{
	class FPSComponent : public BaseComponent
	{
	public:
		FPSComponent(std::weak_ptr<GameObject> pOwningGameObject);
		virtual ~FPSComponent() = default;


		void Update(float deltaTime) override;

		std::shared_ptr<std::string> GetTextLink() const;

		FPSComponent(const FPSComponent&) = delete;
		FPSComponent(FPSComponent&&) noexcept = delete;
		FPSComponent& operator=(const FPSComponent&) = delete;
		FPSComponent& operator=(FPSComponent&&) noexcept = delete;
	private:
		std::shared_ptr<std::string> m_pText;
		float m_AccumulatedTime;
		const float m_UpdateTimeSec;
	};
}
