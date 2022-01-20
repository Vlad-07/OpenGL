#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"


#define assert(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearErrors(); x; assert(GLLogCall(#x, __FILE__, __LINE__))

void GLClearErrors();
bool GLLogCall(const char* function, const char* file, int line);



class Renderer
{
private:


public:
	Renderer();
	~Renderer();

	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

	void Swap(GLFWwindow* window);
	void PollEvents();
};