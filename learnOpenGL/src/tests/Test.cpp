#include "Test.h"
#include "imgui/imgui.h"

namespace test {

test::TestMenu::TestMenu(Test*& currentTestPointer)
:m_currentTest(currentTestPointer)

{
}

test::TestMenu::~TestMenu()
{
}

void test::TestMenu::OnUpdate(float deltaTime)
{
}

void test::TestMenu::OnRender()
{
}

void test::TestMenu::OnImGuiRender()
{
	for (auto& test : m_Tests)
	{
		if (ImGui::Button(test.first.c_str()))
			m_currentTest = test.second();
	}
}

}