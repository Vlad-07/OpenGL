#pragma once

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Triangle
{
private:
	VertexArray m_Va;
	VertexBuffer m_Vb;
	VertexBufferLayout m_Layout;
	IndexBuffer m_Ib;
	Shader m_Shader;

public:

	Triangle() = default;
	Triangle(const void* vb_data, unsigned int vb_data_size, const unsigned int* ib_data, unsigned int ib_count);

	VertexBuffer GetVB() const;
	VertexArray GetVA() const;
	VertexBufferLayout GetLayout() const;
	IndexBuffer GetIB() const;
	Shader GetShader() const;
};