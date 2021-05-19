#include "TestTexture2D.h"

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"imgui/imgui.h"

test::TestTexture2D::TestTexture2D()
	:m_proj(glm::ortho(0.f, 960.f, 0.f, 540.f, -1.0f, 1.0f)),
	 m_view(glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f))),
	 m_translationA(200.f, 0.f, 0.f),m_translationB(400.f, 0.f, 0.f)
{
	float positions[] = 
	{
		-50.f, -50.f,0.f,0.f,
		 50.f,-50.f,1.f,0.f,
		 50.f, 50.f,1.f,1.f,
		-50.f, 50.f,0.f,1.f
	};
	unsigned int indices[] =
	{
		0,1,2,
		2,3,0
	};
	m_VAO = std::make_unique<VertexArray>();
	m_vertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	m_VAO->AddBuffer(*m_vertexBuffer, layout);
	m_indexBuffer = std::make_unique<IndexBuffer>(indices, 6);

	m_proj = glm::ortho(0.f, 960.f, 0.f, 540.f, -1.0f, 1.0f);
	m_view = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f));


	m_shader = std::make_unique<Shader>("src/res/Shader/Basic.shader");
	m_shader->Bind();
	//shader.SetUniform4f("u_color", 0.8f, 0.3f, 0.8f, 1.0f);


	m_texture = std::make_unique<Texture>("src/res/test.png");
	m_texture->Bind(2);
	m_shader->SetUniform1i("u_Texture", 2);

	//m_VAO->UnBind();
	//m_vertexBuffer->UnBind();
	//m_indexBuffer->UnBind();
	//m_shader->UnBind();
}

test::TestTexture2D::~TestTexture2D()
{
}

void test::TestTexture2D::OnUpdate(float deltaTime)
{
}

void test::TestTexture2D::OnRender()
{
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	Renderer render;
	m_VAO->Bind();
	m_indexBuffer->Bind();
	m_texture->Bind();
	m_shader->Bind();
	{
		glm::mat4 model = glm::translate(glm::mat4(1.f), m_translationA);
		glm::mat4 mvp = m_proj * m_view * model;
		m_shader->SetUniformMat4f("u_MVP", mvp);
		render.Draw(*m_VAO, *m_indexBuffer, *m_shader);
	}
	{
		glm::mat4 model = glm::translate(glm::mat4(1.f), m_translationB);
		glm::mat4 mvp = m_proj * m_view * model;
		m_shader->SetUniformMat4f("u_MVP", mvp);
		render.Draw(*m_VAO, *m_indexBuffer, *m_shader);
	}
	
	//if (r < 0.f || r > 1.f)
	//	increment = -increment;
	//r = r + increment;
	

}

void test::TestTexture2D::OnImGuiRender()
{
	//if (show_demo_window)
	////ImGui::ShowDemoWindow(&show_demo_window);
	//if (show_another_window)
	//{
	//	ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
	//	ImGui::Text("Hello from another window!");
	//	if (ImGui::Button("Close Me"))
	//		show_another_window = false;
	//	ImGui::End();
	//}
	//{
	//static float f = 0.0f;
	//static int counter = 0;
	//ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
	//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
	//ImGui::Checkbox("Another Window", &show_another_window);
	//ImGui::SliderFloat3("translationA", &translationA.x, 0.0f, 960.0f);     
	//ImGui::SliderFloat3("translationB", &translationB.x, 0.0f, 960.0f);     
	//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
	//
	//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
	//	counter++;
	//ImGui::SameLine();
	//ImGui::Text("counter = %d", counter);
	//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	//ImGui::End();
	//}
	ImGui::SliderFloat3("translationA", &m_translationA.x, 0.0f, 960.0f);
	ImGui::SliderFloat3("translationB", &m_translationB.x, 0.0f, 960.0f);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
