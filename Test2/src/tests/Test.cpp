#include <stdlib.h>
#include "Test.h"
#include "imgui/imgui.h"

test::TestMenu::TestMenu(Test*& curentTestPtr, std::string& currentTestNamePtr) : m_CurrentTest(curentTestPtr), m_CurrentTestName(&currentTestNamePtr)
{
}

test::TestMenu::~TestMenu()
{
}

void test::TestMenu::OnImguiRender()
{
	for (auto& test : m_Tests)
	{
		if (ImGui::Button(test.first.c_str()))
			m_CurrentTest = test.second(), *m_CurrentTestName = test.first;
	}
	if (ImGui::Button("Terminate app"))
		exit(1);
}