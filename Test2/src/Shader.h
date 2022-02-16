#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

struct ShaderSources
{
	std::string vertexShaderSource;
	std::string fragmentShaderSource;
};

class Shader
{
private:
	unsigned int m_RenderId = 0;
	std::string m_FilePath;
	std::vector<std::pair<std::string, int>> m_UniformCache{};

public:
	Shader() = default;
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	ShaderSources ParseShader(const std::string& filePath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	unsigned int SearchInUniformCache(const std::string& name);
	int GetUniformLocation(const std::string& name);
};