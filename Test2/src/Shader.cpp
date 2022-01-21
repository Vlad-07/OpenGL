#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Renderer.h"

Shader::Shader(const std::string& filepath) : m_FilePath(filepath), m_RenderId(0)
{
	m_FilePath = filepath;
	ShaderSources shaderSources = ParseShader(m_FilePath);
	m_RenderId = CreateShader(shaderSources.vertexShaderSource, shaderSources.fragmentShaderSource);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RenderId));
}

ShaderSources Shader::ParseShader(const std::string& filePath)
{
	enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };


	std::ifstream in(filePath);

	std::stringstream ss[2];
	std::string line;
	ShaderType shaderType = ShaderType::NONE;

	while (std::getline(in, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				shaderType = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				shaderType = ShaderType::FRAGMENT;
		}
		else
			ss[(int)shaderType] << line << '\n';
	}

	return { ss[(int)ShaderType::VERTEX].str(), ss[(int)ShaderType::FRAGMENT].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, NULL));
	GLCall(glCompileShader(id));

	int status;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &status));

	if (status == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* log = new char[length];
		GLCall(glGetShaderInfoLog(id, length, &length, log));

		std::cout << "ERR::COMPILATION::SHADER::";

		switch (type)
		{
		case GL_VERTEX_SHADER:
			std::cout << "VERTEX";
			break;
		case GL_FRAGMENT_SHADER:
			std::cout << "FRAGMENT";
			break;
		default:
			std::cout << "UNKNOWN";
		}
		std::cout << '\n' << log << '\n';

		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}


unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	int status;
	GLCall(glGetProgramiv(program, GL_LINK_STATUS, &status));
	if (status == GL_FALSE)
		std::cout << "Shader_program_link............FAILED\n";
	else
		std::cout << "Shader_program_link............OK\n";

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	std::cout << "Shaders........................OK\n";
	return program;
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RenderId));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

unsigned int Shader::SearchInUniformCache(const std::string& uniformName)
{
	for (int i = 0; i < m_UniformCache.size(); i++)
	{
		if (m_UniformCache[i].first == uniformName)
			return m_UniformCache[i].second;
	}
	return -2;
}

int Shader::GetUniformLocation(const std::string& name)
{
	int location = SearchInUniformCache(name);

	if (location != -2)
		return location;

	GLCall(location = glGetUniformLocation(m_RenderId, name.c_str()));

	if (location == -1)
		std::cout << "[WARNING] Uniform '" + name + "' doesn't exist\n";
	else
		m_UniformCache.push_back(std::make_pair(name, location));

	return location;
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3)
{
	GLCall(glUniform4f(GetUniformLocation(name), f0, f1, f2, f3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}
