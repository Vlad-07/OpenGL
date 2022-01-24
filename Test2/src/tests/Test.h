#pragma once


namespace test
{

	class Test
	{
	protected:
		bool m_ShouldClose = false;

	public:

		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImguiRender() {}

		bool ShouldClose() { return m_ShouldClose; }
		void Reset() { m_ShouldClose = false; }
	};
}
