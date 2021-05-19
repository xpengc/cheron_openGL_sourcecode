#pragma once
#include"Test.h"
#include"../VertexBuffer.h"
#include"../IndexBuffer.h"
#include"../VertexArray.h"
#include"../Shader.h"
#include"../Texture.h"
#include<memory>
namespace test {
	class TestTexture2D :public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();
		void OnUpdate(float deltaTime);
		void OnRender();
		void OnImGuiRender();

	private:
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<IndexBuffer> m_indexBuffer;
		std::unique_ptr<Texture> m_texture;
	private:
		glm::vec3 m_translationA;
		glm::vec3 m_translationB;
		glm::mat4 m_proj;
		glm::mat4 m_view;
	};

}

