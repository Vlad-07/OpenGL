#include "Renderer.h"
#include <iostream>


void GLClearErrors()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function << ' ' << file << ':' << line << '\n';
		return false;
	}
	return true;
}




Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
	shader.Bind();
	va.Bind();
	ib.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(const Triangle& triangle, const Shader& shader)
{
	shader.Bind();
	triangle.GetVA().Bind();
	triangle.GetIB().Bind();

	GLCall(glDrawElements(GL_TRIANGLES, triangle.GetIB().GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Swap(GLFWwindow* window)
{
	glfwSwapBuffers(window);
}

void Renderer::PollEvents()
{
	glfwPollEvents();
}
