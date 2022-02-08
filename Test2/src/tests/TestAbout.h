#pragma once

#include "Test.h"

namespace test
{
	class About : public test::Test
	{
	private:
		bool m_ShowDemo = false;

	public:
		About();
		~About();

		virtual void OnImguiRender() override;
	};
}