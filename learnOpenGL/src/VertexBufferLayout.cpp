#include "VertexBuffer.h"
#include"Renderer.h"
#include "VertexBufferLayout.h"

const std::vector<VertexBufferElement>& VertexBufferLayout::GetElements() const
{
	return m_Elements;
}
