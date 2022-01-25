#include "TestClearColor.h"
#include "Renderer.h"
#include "imgui/imgui.h"

test::ClearColor::ClearColor() : m_ClearColor{ 0.2f, 0.5f, 0.3f, 1.8f }
{
}

test::ClearColor::~ClearColor()
{
}

void test::ClearColor::OnUpdate(float deltaTime)
{
}

void test::ClearColor::OnRender()
{
	GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void test::ClearColor::OnImguiRender()
{
	ImGui::ColorPicker4("Clear color", m_ClearColor);
}
