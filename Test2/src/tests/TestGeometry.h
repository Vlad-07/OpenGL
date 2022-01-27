#pragma once
#include "Test.h"
#include "Renderer.h"

namespace test
{
	class Geometry : public Test
	{
	private:
		int m_ShapeCount = 2;

		Renderer renderer;
		VertexArray* m_Va;
		VertexBuffer* m_Vb;
		VertexBufferLayout* m_Layout;
		IndexBuffer* m_Ib;
		Shader* m_Shader;


		float vertices[25] = {
			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,  0.0f, 1.0f,
			-0.5f,  0.8f,0.0f,  0.0f, 0.0f
		};


		unsigned int indicesA[3] = {
			0, 1, 2
		};

	public:

		Geometry();
		~Geometry();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;
	};
}