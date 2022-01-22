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
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define WindowWidth 960
#define WindowHeight 540

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
	MouseX = xpos;
	MouseY = ypos;
}


int main(void)
{
	std::cout << "Begin...\n\n";

	CheckGLFW();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window;
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	
	glfwWindowHint(GLFW_SAMPLES, 16);
	window = glfwCreateWindow(WindowWidth, WindowHeight, "window", NULL, NULL);

	CheckWindow(window);

	glfwSetCursorPosCallback(window, cursor_position_callback);

	glfwMakeContextCurrent(window);

	CheckGLEW();

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glBlendEquation(GL_FUNC_ADD));

	GLCall(glEnable(GL_MULTISAMPLE));
	GLCall(glfwSwapInterval(1));



	float vertices[] = {
		 100.0f, 100.0f, 0.0f,  0.0f, 0.0f,
		 200.0f, 100.0f, 0.0f,  1.0f, 0.0f,
		 200.0f, 200.0f, 0.0f,  1.0f, 1.0f,
		 100.0f, 200.0f, 0.0f,  0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};



	VertexArray va;
	VertexBuffer vb(vertices, 4 * 5 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 2 * 3 * sizeof(float));
	

	glm::mat4 proj = glm::ortho(0.0f, (float)WindowWidth, 0.0f, (float)WindowHeight, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-50, 350, 0));

	glm::mat4 mvp = proj * view * model;

	Shader shader("res/shaders/basic.shader");

	shader.Bind();
	shader.SetUniformMat4f("u_MVP", mvp);

	Texture tex("res/textures/image.png");
	tex.Bind();
	shader.SetUniform1i("u_Texture", 0);

	Renderer renderer;


	std::cout << "\n\n\n";
	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();


		view = glm::translate(glm::mat4(1.0f), glm::vec3(MouseX, MouseY * -1, 0));
		glm::mat4 mvp = proj * view * model;
		shader.SetUniformMat4f("u_MVP", mvp);

		shader.Bind();

		renderer.Draw(va, ib, shader);

		renderer.Swap(window);
		renderer.PollEvents();
	}

//	glfwTerminate();
	return 0;
}