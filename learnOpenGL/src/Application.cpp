#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"Renderer.h"
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"
#include"Texture.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw.h"
#include"imgui/imgui_impl_opengl3.h"
#include"tests/TestClearColor.h"
#include"tests/TestTexture2D.h"


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library*/
	if (!glfwInit())
		return -1;

	/* Creat a windowed mode window and its OpenGL context*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/*Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(5);
#if defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
	{
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR!" << std::endl;
	}
	}
#endif

	std::cout << glGetString(GL_VERSION) << std::endl;
	{
		
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA))

		Renderer render;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330 core");
		ImGui::StyleColorsDark();
		
		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;
		testMenu->RegisterTest<test::TestClearColor>("Clear Color");
		testMenu->RegisterTest<test::TestTexture2D>("2D Texture ");


		while (!glfwWindowShouldClose(window))
		{
			/*Render here*/
			render.Clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			//test.OnImGuiRender();
			if (currentTest)
			{
				currentTest->OnUpdate(0.f);
				currentTest->OnRender();
				ImGui::Begin("Test");
				if (currentTest != testMenu && ImGui::Button("<-"))
				{
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->OnImGuiRender();
				ImGui::End();

			}
			/*swap front and back buffers*/
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			
			glfwSwapBuffers(window);
			/*Poll for and process enents*/
			glfwPollEvents();
		}
		if (currentTest != testMenu)
			delete testMenu;
		delete currentTest;

	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0; 
}