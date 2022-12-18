#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const std::string& filepath)
	: m_Filepath(filepath),m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))//getline need to include <string>
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				//set mode to vertex
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				//set mode to fragment
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//Error handing
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int lengh;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lengh);
		char* message = (char*)malloc(lengh * sizeof(char));
		glGetShaderInfoLog(id, lengh, &lengh, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& VertexShader, const std::string& FragmentShader)//two kinds of strings are the actual shader code
{
	unsigned int program = glCreateProgram();//Create a shader program
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, VertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);//delete the source after link
	glDeleteShader(fs);

	return program;
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}


void Shader::SetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}



void Shader::SetUniform2f(const std::string& name, const glm::vec2& value)
{
	GLCall(glUniform2f(GetUniformLocation(name), value.x, value.y));
}

void Shader::SetUniform3f(const std::string& name, const glm::vec3& value)
{
	GLCall(glUniform3f(GetUniformLocation(name), value.x, value.y, value.z));
}

void Shader::SetUniform4f(const std::string& name, const glm::vec4& value)
{
	GLCall(glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}
unsigned int Shader::GetUniformLocation(const std::string& name)
{
	//By using cache to optimization 
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

	m_UniformLocationCache[name] = location;
	return location;
}