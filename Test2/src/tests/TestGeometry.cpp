#include "TestGeometry.h"
#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


test::Geometry::Geometry()
{
	m_Va = new VertexArray();
	m_Vb = new VertexBuffer(vertices, 5 * 5 * sizeof(float));
	m_Layout = new VertexBufferLayout();

	m_Ib = new IndexBuffer(indicesA, 3 * sizeof(float));

	m_Layout->Push<float>(3);
	m_Layout->Push<float>(2);
	m_Va->AddBuffer(*m_Vb, *m_Layout);



	m_Shader = new Shader("res/shaders/basic.shader");
	m_Shader->Bind();
	m_Shader->SetUniform1i("u_Texture", 0);

	glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	glm::mat4 mvp = proj;

	m_Shader->SetUniformMat4f("u_MVP", mvp);
	m_Shader->SetUniform4f("u_ColorOff", 0.2f, 0.2f, 0.5f, 1.0f);
}

test::Geometry::~Geometry()
{
	delete m_Va;
	delete m_Vb;
	delete m_Layout;
	delete m_Ib;
	delete m_Shader;
}

void test::Geometry::OnUpdate(float deltaTime)
{
}

void test::Geometry::OnRender()
{
	renderer.DrawOverrided(*m_Va, *m_Ib, *m_Shader, m_ShapeCount * 3);
}

void test::Geometry::OnImguiRender()
{
	ImGui::SliderInt("Shape Count", &m_ShapeCount, 0, 3);
}