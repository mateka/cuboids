#include <gllib/shader.h>
#include <iostream>
#include <string>
#include <vector>


namespace gllib {

shader::shader(const gl::GLenum type, const char* code)
	: m_shaderid{ gl::glCreateShader(type) }
{
	if (!m_shaderid)
		throw glerror();
	gl::glShaderSource(m_shaderid, 1, &code, nullptr);
	gl::glCompileShader(m_shaderid);

	gl::GLint logLength = 0;
	gl::glGetShaderiv(m_shaderid, gl::GLenum::GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0) {
		std::vector<gl::GLchar> log(logLength + 1);
		gl::glGetShaderInfoLog(m_shaderid, logLength, nullptr, &log[0]);
		std::cout
			<< std::string(20, '=')
			<< "Shader compilation status:\n" << log.data()
			<< std::string(20, '=') << std::endl;
	}
	gl::GLboolean result;
	gl::glGetShaderbv(m_shaderid, gl::GLenum::GL_COMPILE_STATUS, &result);
	if (result == gl::GL_FALSE)
		throw shader_compilation_error();
}

shader::shader(shader&& other)
	: m_shaderid{ other.m_shaderid }
{
	other.m_shaderid = 0;
}

shader& shader::operator=(shader&& other) {
	if (this != &other) {
		m_shaderid = other.m_shaderid;
		other.m_shaderid = 0;
	}
	return *this;
}

shader::~shader() {
	if(m_shaderid)
		gl::glDeleteShader(m_shaderid);
}


shader_compilation_error::shader_compilation_error()
	: runtime_error{ "Shader compilation failed" }
{}

}
