#pragma once
#include<vector>
#include<GL/glew.h>
#include"Renderer.h"

struct VertexBufferElement
{
	unsigned int count;
	unsigned int type;
	unsigned char normalized;

	static unsigned int GetSizeofType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT:return 4;
		case GL_UNSIGNED_BYTE:return 1;
		}
		ASSERT(false);
		return 0;
	}

};

class VertexBufferLayout
{
public:
	VertexBufferLayout()
		:m_stride(0)
	{

	}
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_stride;

public:
	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push <float>(unsigned int count)
	{
		m_Elements.push_back({ count,GL_FLOAT,false });
		m_stride += VertexBufferElement::GetSizeofType(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ count,GL_UNSIGNED_INT,false });
		m_stride += VertexBufferElement::GetSizeofType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ count,GL_UNSIGNED_BYTE,true });
		m_stride += VertexBufferElement::GetSizeofType(GL_UNSIGNED_BYTE) * count;
	}

	const std::vector<VertexBufferElement>& GetElements() const;
	inline const int GetStride() const { return m_stride; }

};

