#pragma once

namespace StreamEngine
{
	class BaseComponent
	{
	public:
		BaseComponent();
		virtual ~BaseComponent();

		virtual void run() = 0;
		
		BaseComponent(const BaseComponent&) = delete;
		BaseComponent(BaseComponent&&) noexcept = delete;
		BaseComponent& operator=(const BaseComponent&) = delete;
		BaseComponent& operator=(BaseComponent&&) noexcept = delete;
	private:
		
	};
}
