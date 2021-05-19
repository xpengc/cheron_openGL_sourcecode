#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
Shader::Shader(const std::string& filePath)
	:m_RenderID(0),m_filePath(filePath)
{
	ShaderProgramSource source =ParseShader(filePath);
	m_RenderID = CreateShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RenderID));
}

ShaderProgramSource Shader::ParseShader(const std::string& filePath)
{
	std::ifstream fileStream(filePath);
	std::string line;
	std::stringstream sstr[2];
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	ShaderType type = ShaderType::NONE;
	while (std::getline(fileStream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			sstr[(int)type] << line << '\n';
		}
	}
	return { sstr[0].str(),sstr[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	// process error
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int len;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
		char* message = (char*)alloca(len * sizeof(char));
		glGetShaderInfoLog(id, len, &len, message);
		std::cout << "Failed to complie" <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader ! " << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLCall(unsigned int program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);
	//glDeleteShader(vs);
	//glDeleteShader(fs);

	return program;
}

void Shader::Bind() const
{
	glUseProgram(m_RenderID);
}

void Shader::UnBind() const
{
	glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	int loc = GetUniformLocation(name);
	GLCall(glUniform1i(loc, value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	int loc = GetUniformLocation(name);
	GLCall(glUniform1f(loc, value));
}

void Shader::SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3)
{
	int loc = GetUniformLocation(name);
	GLCall(glUniform4f(loc, f0, f1, f2, f3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	int loc = GetUniformLocation(name);
	GLCall(glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	int loc = glGetUniformLocation(m_RenderID,name.c_str());
	if (loc == -1)
		std::cout << "warning:" << name << " doesn't exist !" << std::endl;
	else
		m_UniformLocationCache[name] = loc;
	return loc;
}
