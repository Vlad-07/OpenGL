#pragma once
#include "Test.h"

namespace test
{
	class ClearColor : Test
	{
	private:
		float m_ClearColor[4];

	public:
		ClearColor();
		~ClearColor();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;
	};
}