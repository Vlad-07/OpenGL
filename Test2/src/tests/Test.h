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
		std::vector < std::pair<std::string, std::function<Test* ()>>> m_Tests;

	public:
		TestMenu(Test*& curentTestPtr);
		~TestMenu();

		void OnImguiRender() override;

		template<typename T>
		void RegisterTest(const std::string& testName)
		{
			std::cout << testName << " test registration";
			for (int i = testName.length() + 18; i <= 31; i++, std::cout << '.');
			std::cout << "unhandeled test type \n";
			assert(false);
		}

		template<>
		void RegisterTest<test::ClearColor>(const std::string& testName)
		{
			std::cout << "Registering test: " << testName << '\n';
			m_Tests.push_back(std::make_pair(testName, []() { return new test::ClearColor(); }));
		}
	};
}
