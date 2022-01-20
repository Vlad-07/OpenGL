#pragma once

#include "VertexBuffer.h"

extern class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_RendererId;

public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout &layout);
};