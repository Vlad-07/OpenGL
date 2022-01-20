#include "Triangle.h"

Triangle::Triangle(const void* vb_data, unsigned int vb_data_size, const unsigned int* ib_data, unsigned int ib_count)
{
	m_Vb = VertexBuffer(vb_data, vb_data_size);
	m_Ib = IndexBuffer(ib_data, ib_count);
}

VertexBuffer Triangle::GetVB() const
{
	return m_Vb;
}

VertexArray Triangle::GetVA() const
{
	return m_Va;
}

VertexBufferLayout Triangle::GetLayout() const
{
	return m_Layout;
}

IndexBuffer Triangle::GetIB() const
{
	return m_Ib;
}

Shader Triangle::GetShader() const
{
	return m_Shader;
}
