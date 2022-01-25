#include "Test.h"
#include "imgui/imgui.h"

test::TestMenu::TestMenu(Test*& curentTestPtr) : m_CurrentTest(curentTestPtr)
{
}

test::TestMenu::~TestMenu()
{
}

void test::TestMenu::OnImguiRender()
{
	ImGui::Begin("Test list");
	for (auto& test : m_Tests)
	{
		if (ImGui::Button(test.first.c_str()))
			m_CurrentTest = test.second();
	}
	if (ImGui::Button("Terminate app"))
		exit(1);
	ImGui::End();
}

