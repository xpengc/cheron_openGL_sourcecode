#include "Renderer.h"
#include<iostream>
#include"VertexArray.h"
#include"IndexBuffer.h"
#include"Shader.h"
#include<GL/glew.h>
void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogaCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error](" << error << "):" << function
			<< " " << file << ":" << line << " " << std::endl;
		return false;
	}
	return true;
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
	
		shader.Bind();
		va.Bind();
		ib.Bind();
		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);

	
}
