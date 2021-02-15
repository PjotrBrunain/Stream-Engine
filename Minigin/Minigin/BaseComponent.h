#pragma once

namespace StreamEngine
{
	class BaseComponent
	{
	public:
		BaseComponent();
		~BaseComponent();

		BaseComponent(const BaseComponent&) = delete;
		BaseComponent(BaseComponent&&) noexcept = delete;
		BaseComponent& operator=(const BaseComponent&) = delete;
		BaseComponent& operator=(BaseComponent&&) noexcept = delete;
	private:
		
	};
}
