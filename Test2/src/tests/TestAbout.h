#pragma once

#include "Test.h"

namespace test
{
	class About : public test::Test
	{
	public:
		About();
		~About();

		virtual void OnImguiRender() override;
	};
}