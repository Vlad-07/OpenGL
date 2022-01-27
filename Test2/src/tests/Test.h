#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>

namespace test
{

	class Test
	{
	public:

		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImguiRender() {}
	};

	class TestMenu : public Test
	{
	private:
		Test*& m_CurrentTest;
		std::string* m_CurrentTestName;

	public:
		std::vector <std::pair<std::string, std::function<Test* ()>>> m_Tests;

	public:
		TestMenu(Test*& curentTestPtr, std::string& currentTestNamePtr);
		~TestMenu();

		void OnImguiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Reg test " << name << '\n';
			m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
		}
	};
}
