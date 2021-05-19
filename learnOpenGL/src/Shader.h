#pragma once
#include"Renderer.h"
#include<string>
#include<unordered_map>
#include<glm/glm.hpp>

struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader
{
private:
	unsigned int m_RenderID;
	std::string m_filePath;
	std::unordered_map<std::string, unsigned int> m_UniformLocationCache;
public:
	Shader(const std::string& filePath);
	~Shader();
	ShaderProgramSource ParseShader(const std::string& filePath);

	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	void Bind() const;
	void UnBind() const;
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
	int GetUniformLocation(const std::string& name);
};

