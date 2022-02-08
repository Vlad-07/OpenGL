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
		TestType m_ActiveTexture = TestType::ColorTest;
		Texture m_ColorTest;
		Texture m_BlendTest;

		Renderer renderer;
		VertexArray* m_Va;
		VertexBuffer* m_Vb;
		VertexBufferLayout* m_Layout;
		IndexBuffer* m_Ib;
		Shader* m_Shader;


		float vertices[20] = {
		 -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
		  1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		  1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
		 -1.0f,  1.0f, 0.0f,  0.0f, 1.0f
		};

		unsigned int indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		static bool m_Blending;

	public:

		TextureTest();
		~TextureTest();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;
	};

}