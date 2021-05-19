#pragma once
#include<GL/glew.h>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogaCall(#x,__FILE__,__LINE__));

void GLClearError();

bool GLLogaCall(const char* function, const char* file, int line);

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer
{
public :
	void Clear();
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) ;
};