#pragma once
#include "Test.h"
#include "Renderer.h"
#include "Texture.h"

namespace test
{
	class TextureTest : public Test
	{
	private:
		enum class TestType { ColorTest = 0, BlendingTest };
		TestType m_ActiveTexture;
		Texture m_ColorTest;
		Texture m_BlendTest;

	public:

		TextureTest();
		~TextureTest();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;
	};

}