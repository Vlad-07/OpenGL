#include <iostream>
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

static void GenImGuiIni(bool generate)
{
	if (!generate)
		return;

	std::ofstream out("imgui.ini");

	std::string file = R"([Window][Debug##Default]
Pos=299,99
Size=424,395
Collapsed=0

[Window][Debug]
Pos=15,14
Size=316,72
Collapsed=0

[Window][Test Menu]
Pos=15,95
Size=199,238
Collapsed=0

[Window][Clear Color Test]
Pos=15,95
Size=315,336
Collapsed=0

[Window][Geometry Test]
Pos=15,95
Size=358,143
Collapsed=0

[Window][Window]
Pos=70,45
Size=386,360
Collapsed=0

[Window][NULL]
Pos=60,60
Size=115,123
Collapsed=0

[Window][Texture Test]
Pos=15,95
Size=179,179
Collapsed=0

[Window][About]
Pos=15,95
Size=604,261
Collapsed=0

[Window][Dear ImGui Demo]
Pos=389,49
Size=560,680
Collapsed=0

[Window][Dear ImGui Metrics/Debugger]
Pos=-19,62
Size=339,273
Collapsed=0

[Window][Dear ImGui Stack Tool]
Pos=60,60
Size=354,104
Collapsed=0

[Window][]
Pos=256,217
Size=724,112
Collapsed=0

[Window][##]
Pos=247,206
Size=710,61
Collapsed=0
)";

	out << file;
}

static void CheckGLFW()
{
	if (!glfwInit())
		std::cout << "GLFW...........................FAILED\n";
	else
		std::cout << "GLFW...........................OK\n";
}
static void CheckGLEW()
{
	if (glewInit() != GLEW_OK)
		std::cout << "GLEW...........................FAILED\n";
	else
		std::cout << "GLEW...........................OK\n";
}
static void InitImGui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	ImGui::StyleColorsDark();
}
static void CheckWindow(GLFWwindow* window)
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
static void PrintStats()
{
	std::cout << "\nOpenGL renderer:\n";
	std::cout << " Vendor........................." << glGetString(GL_VENDOR) << '\n';
	std::cout << " Renderer......................." << glGetString(GL_RENDERER) << '\n';
	std::cout << " Version........................" << glGetString(GL_VERSION) << "\n\n";
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

	GenImGuiIni(true);

	int w = -1, h = -1, samples = 8;
	std::cout << "Input window width, height and aa samples (-1 for default)\n";
	std::cin >> w >> h >> samples;

	if (w != -1)
		WindowWidth = w;

	if (h != -1)
		WindowHeight = h;

	if (samples < 0)
		samples = 4;

	std::cout << "Begin...\n";
	CheckGLFW();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, samples);

	GLFWwindow* window;
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	window = glfwCreateWindow(WindowWidth, WindowHeight, "Window", NULL, NULL);
	CheckWindow(window);
	glfwMakeContextCurrent(window);

	glfwSetCursorPosCallback(window, cursor_position_callback);

	CheckGLEW();

	PrintStats();

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
		// Loading screen animation
		if (starting) 
		{
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			renderer.Clear();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGuiWindowFlags windowFlags = 0;
			windowFlags |= ImGuiWindowFlags_NoTitleBar;
			windowFlags |= ImGuiWindowFlags_NoScrollbar;
			windowFlags |= ImGuiWindowFlags_NoMove;
			windowFlags |= ImGuiWindowFlags_NoResize;
			windowFlags |= ImGuiWindowFlags_NoCollapse;
			windowFlags |= ImGuiWindowFlags_NoNav;
			windowFlags |= ImGuiWindowFlags_NoBackground;
			windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
			bool* o = nullptr;

			ImGui::Begin("##", o, windowFlags);

			static float progress = 0.0f, step = 0.01f;
			progress += step * ImGui::GetIO().DeltaTime;

			Random random;
			if (random.RandomNumber(0, 100) > 99)
				step = random.RandomNumber(0.1f, 0.4f);

			if (progress >= +1.05f)
				starting = false;
			ImGui::SameLine(200);
			ImGui::Text("Loading...");
			ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
			ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);

			ImGui::End();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			renderer.Swap(window);
			renderer.PollEvents();
			continue;
		}


		GLCall(glClearColor(0.03f, 0.03f, 0.03f, 1.0f));
		renderer.Clear();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		if (currentTest)
		{
			ImGuiWindowFlags windowFlags = 0;
			windowFlags |= ImGuiWindowFlags_NoMove;
			windowFlags |= ImGuiWindowFlags_NoResize;
			windowFlags |= ImGuiWindowFlags_NoCollapse;

			ImGui::Begin(currentTestName.c_str(), 0, windowFlags);

			currentTest->OnUpdate(0);
			currentTest->OnRender();
			currentTest->OnImguiRender();

			if (currentTest != testMenu && ImGui::Button("Close"))
				delete currentTest, currentTest = testMenu, currentTestName = "Test Menu";
			ImGui::End();
			
			ImGui::Begin("Debug", 0, windowFlags);
			ImGui::Text("Frametime: %.3f ms (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
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
}
