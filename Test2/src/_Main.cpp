#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <chrono>
#include <vector>
#include <iomanip>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"


#define WindowWidth 800
#define WindowHeight 600

double Map(double x, double in_min, double in_max, double out_min, double out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


inline void CheckGLFW()
{
	if (!glfwInit())
		std::cout << "GLFW...........................FAILED\n";
	else
		std::cout << "GLFW...........................OK\n";
}

inline void CheckGLEW()
{
	if (glewInit() != GLEW_OK)
		std::cout << "GLEW...........................FAILED\n";
	else
		std::cout << "GLEW...........................OK\n";
}

inline void CheckWindow(GLFWwindow* window)
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


float MouseX = 0, MouseY = 0;

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	MouseX = Map(xpos, 0, WindowWidth, -1, 1);
	MouseY = Map(ypos, 0, WindowHeight, -1, 1);

}


int main(void)
{
	std::cout << "Begin...\n\n";

	CheckGLFW();

	GLFWwindow* window;
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	
	glfwWindowHint(GLFW_SAMPLES, 16);
	window = glfwCreateWindow(WindowWidth, WindowHeight, "window", NULL, NULL);

	CheckWindow(window);

	glfwSetCursorPosCallback(window, cursor_position_callback);

	glfwMakeContextCurrent(window);

	CheckGLEW();

	glEnable(GL_MULTISAMPLE);
	glfwSwapInterval(1);


	float vertices[] = {
		-0.25f, -0.25f,
		 0.25f, -0.25f,
		 0.25f,  0.25f,
		-0.25f,  0.25f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};


	Triangle tri(vertices, 2 * 4 * sizeof(float), indices, 2 * 3 * sizeof(float));

	tri.GetLayout().Push<float>(2);

	tri.GetVA().AddBuffer(tri.GetVB(), tri.GetLayout());

	IndexBuffer ib(indices, 2 * 3 * sizeof(float));
	

	Shader shader("res/shaders/basic.shader");

	shader.Bind();
	shader.SetUniform4f("u_Color", 0.5f, 0.2f, 0.5f, 1.0f);

	Renderer renderer;


	std::cout << "\n\n\n";
	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();

		shader.Bind();

		shader.SetUniform4f("u_Color", MouseX, MouseY, 0.2f, 1.0f);
		

		shader.SetUniform4f("offset", MouseX, MouseY * -1, 0.0f, 0.0f);
		renderer.Draw(tri, shader);

		renderer.Swap(window);
		renderer.PollEvents();
	}

//	glfwTerminate();
	return 0;
}