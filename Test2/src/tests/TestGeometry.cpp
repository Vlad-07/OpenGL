#include "TestGeometry.h"
#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <gl/glew.h>

int test::Geometry::m_VSync = 1;

test::Geometry::Geometry() : m_Shader("res/shaders/basic.shader")
{
	m_Vb = new VertexBuffer(vertices, 5 * 5 * sizeof(float));
	m_Ib = new IndexBuffer(indicesA, 3 * sizeof(float));

	m_Layout.Push<float>(3);
	m_Layout.Push<float>(2);
	m_Va.AddBuffer(*m_Vb, m_Layout);


	m_Shader.Bind();
	m_Shader.SetUniform1i("u_Texture", 0);

	glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	glm::mat4 mvp = proj;

	m_Shader.SetUniformMat4f("u_MVP", mvp);
	m_Shader.SetUniform4f("u_ColorOff", 0.2f, 0.2f, 0.5f, 1.0f);
}

test::Geometry::~Geometry()
{
	delete m_Vb;
	delete m_Ib;
}

void test::Geometry::OnUpdate(float deltaTime)
{
}

void test::Geometry::OnRender()
{
	GLCall(glfwSwapInterval(m_VSync));
	renderer.DrawOverrided(m_Va, *m_Ib, m_Shader, m_ShapeCount * 3);
}

void test::Geometry::OnImguiRender()
{
	ImGui::InputInt("VSync", &m_VSync);
	if (m_VSync < 0)
		m_VSync = 0;

	ImGui::NewLine();

	ImGui::SliderInt("Shape Count", &m_ShapeCount, 0, 3);
}