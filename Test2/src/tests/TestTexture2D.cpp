#include "TestTexture2D.h"
#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

test::TextureTest::TextureTest() :	m_ColorTest("C:/dev/OpenGL/Test2/Test2/res/textures/Color_Test_Texture.png"),
									m_BlendTest("C:/dev/OpenGL/Test2/Test2/res/textures/Transparency-Blending_Test_Texture.png")
{
	m_Va = new VertexArray();
	m_Vb = new VertexBuffer(vertices, 4 * 5 * sizeof(float));
	m_Layout = new VertexBufferLayout();
	m_Ib = new IndexBuffer(indices, 2 * 3 * sizeof(float));
	m_Shader = new Shader("res/shaders/basic.shader");

	m_Layout->Push<float>(3);
	m_Layout->Push<float>(2);
	m_Va->AddBuffer(*m_Vb, *m_Layout);

	m_Shader->Bind();
	m_Shader->SetUniform1i("u_Texture", 0);

	glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	glm::mat4 mvp = proj;

	m_Shader->SetUniformMat4f("u_MVP", mvp);
}

test::TextureTest::~TextureTest()
{
	delete m_Va;
	delete m_Vb;
	delete m_Layout;
	delete m_Ib;
	delete m_Shader;
}

void test::TextureTest::OnUpdate(float deltaTime)
{
}

void test::TextureTest::OnRender()
{
	switch (m_ActiveTexture)
	{
	case test::TextureTest::TestType::ColorTest:
		m_ColorTest.Bind();
		break;
	case test::TextureTest::TestType::BlendingTest:
		GLCall(glClearColor(0.3f, 0.7f, 0.25f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		m_BlendTest.Bind();
		break;
	default:
		assert(false);
	}

	renderer.Draw(*m_Va, *m_Ib, *m_Shader);
	
}

void test::TextureTest::OnImguiRender()
{
	switch (m_ActiveTexture)
	{
	case test::TextureTest::TestType::ColorTest:
		ImGui::Text("Color Test");
		break;
	case test::TextureTest::TestType::BlendingTest:
		ImGui::Text("Blending Test");
		break;
	default:
		assert(false);
	}

	if (ImGui::Button("Swap texture"))
	{
		if (m_ActiveTexture == TestType::ColorTest)
			m_ActiveTexture = TestType::BlendingTest;
		else if (m_ActiveTexture == TestType::BlendingTest)
			m_ActiveTexture = TestType::ColorTest;
	}
}