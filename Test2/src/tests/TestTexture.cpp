#include "TestTexture.h"
#include "imgui/imgui.h"

test::TextureTest::TextureTest() :	m_ColorTest("C:/dev/OpenGL/Test2/Test2/res/textures/Color_Test_Texture.png"),
									m_BlendTest("C:/dev/OpenGL/Test2/Test2/res/textures/Transparency-Blending_Test_Texture.png")
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};



	VertexArray va;
	VertexBuffer vb(vertices, 4 * 4 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 2 * 3 * sizeof(float));


	Shader shader("res/shaders/basic.shader");

	shader.Bind();
	shader.SetUniform4f("u_Color", 0.5f, 0.2f, 0.5f, 1.0f);
	shader.SetUniform1i("u_Texture", 0);

	Texture tex("res/textures/image.png");
	tex.Bind();
}

test::TextureTest::~TextureTest()
{
}

void test::TextureTest::OnUpdate(float deltaTime)
{
}

void test::TextureTest::OnRender()
{
	
}

void test::TextureTest::OnImguiRender()
{
	if (ImGui::Button("Swap texture"))
	{
		if (m_ActiveTexture == TestType::ColorTest)
			m_ActiveTexture = TestType::BlendingTest;
		else if (m_ActiveTexture == TestType::BlendingTest)
			m_ActiveTexture = TestType::ColorTest;
	}
}
