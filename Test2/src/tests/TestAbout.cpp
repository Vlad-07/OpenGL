#include "TestAbout.h"

#include "imgui/imgui.h"

namespace test
{
	About::About()
	{
	}

	About::~About()
	{
	}

	void About::OnImguiRender()
	{
		std::string buffer = R"(#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <chrono>
#include <vector>
#include <iomanip>
#include <Windows.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"
#include "tests/TestGeometry.h"
#include "tests/TestAbout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

static int WindowWidth = 960;
static int WindowHeight = 540;

static double Map(double x, double in_min, double in_max, double out_min, double out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
struct Random
{
private:
	std::default_random_engine engine;

public:
	Random()
	{
		engine.seed(std::chrono::system_clock::now().time_since_epoch().count());
	}

	float RandomNumber(float min, float max)
	{
		std::uniform_real_distribution<float> random(min, max);

		return random(engine);
	}
};


static inline void CheckGLFW()
{
	if (!glfwInit())
		std::cout << "GLFW...........................FAILED\n";
	else
		std::cout << "GLFW...........................OK\n";
}
static inline void CheckGLEW()
{
	if (glewInit() != GLEW_OK)
		std::cout << "GLEW...........................FAILED\n";
	else
		std::cout << "GLEW...........................OK\n";
}
static inline void InitImGui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	ImGui::StyleColorsDark();
}
static inline void CheckWindow(GLFWwindow* window)
{
	if (!window)
	{
		std::cout << "GLFW_window_init...............FAILED\n";
		std::cin.get();
		glfwTerminate();
		exit(-1);
	}
	std::cout << "GLFW_WINDOW....................OK\n";
}

float MouseX = 0, MouseY = 0;

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	MouseX = xpos;
	MouseY = ypos;
}

int main(void)
{
	// TODO: dvd test


	int w = -1, h = -1;
	std::cout << "Input window width and height (-1 for default)\n";
	std::cin >> w >> h;

	if (w != -1)
		WindowWidth = w;

	if (h != -1)
		WindowHeight = h;

	std::cout << "Begin...\n";
	CheckGLFW();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 16);

	GLFWwindow* window;
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	window = glfwCreateWindow(WindowWidth, WindowHeight, "Window", NULL, NULL);
	CheckWindow(window);
	glfwMakeContextCurrent(window);

	glfwSetCursorPosCallback(window, cursor_position_callback);

	CheckGLEW();

	std::cout << "\nOpenGL renderer:\n";
	std::cout << " Vendor........................." << glGetString(GL_VENDOR) << '\n';
	std::cout << " Renderer......................." << glGetString(GL_RENDERER) << '\n';
	std::cout << " Version........................" << glGetString(GL_VERSION) << "\n\n";

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glBlendEquation(GL_FUNC_ADD));

	GLCall(glEnable(GL_MULTISAMPLE));
	GLCall(glfwSwapInterval(1));

	InitImGui(window);


	Renderer renderer;

	bool shouldClose = false;

	std::string currentTestName = "Test Menu";
	test::Test* currentTest = nullptr;
	test::TestMenu* testMenu = new test::TestMenu(currentTest, currentTestName, &shouldClose);
	currentTest = testMenu;


	testMenu->RegisterTest<test::ClearColor>("Clear Color Test");
	testMenu->RegisterTest<test::TextureTest>("Texture Test");
	testMenu->RegisterTest<test::Geometry>("Geometry Test");
	testMenu->RegisterTest<test::About>("About");

	
	bool starting = true;


	std::cout << "\n\n";
	while (!glfwWindowShouldClose(window) && !shouldClose)
	{
		GLCall(glClearColor(0.03f, 0.03f, 0.03f, 1.0f));
		renderer.Clear();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		if (currentTest)
		{
			ImGui::Begin(currentTestName.c_str());

			currentTest->OnUpdate(0);
			currentTest->OnRender();
			currentTest->OnImguiRender();

			if (currentTest != testMenu && ImGui::Button("Close"))
				delete currentTest, currentTest = testMenu, currentTestName = "Test Menu";
			ImGui::End();
			
			ImGui::Begin("Debug");
			ImGui::Text("Frametime: %.3f ms (%.1f FPS) ", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
	}


	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	renderer.Swap(window);
	renderer.PollEvents();
}

if (currentTest != testMenu)
delete testMenu;
delete currentTest;

ImGui_ImplOpenGL3_Shutdown();
ImGui_ImplGlfw_Shutdown();
ImGui::DestroyContext();
glfwTerminate();

std::cout << "Cleanup........................OK";

return 0;
})";

		ImGui::Text("Vlad_");
		ImGui::NewLine();
		ImGui::Text("_Main.cpp");
		ImGui::InputTextMultiline("##src", (char*)buffer.c_str(), sizeof(buffer));
	}
}