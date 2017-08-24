#include <gllib/program.h>
#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>


namespace gllib {

program::program(std::initializer_list<shader> shaders)
	: m_programid(gl::glCreateProgram())
{
	if (!m_programid)
		throw glerror();
	for (const auto& s : shaders)
		gl::glAttachShader(m_programid, s.m_shaderid);
	gl::glLinkProgram(m_programid);

	gl::GLint logLength = 0;
	gl::glGetProgramiv(m_programid, gl::GLenum::GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0) {
		std::vector<gl::GLchar> log(logLength + 1);
		gl::glGetProgramInfoLog(m_programid, logLength, nullptr, &log[0]);
		std::cout
			<< std::string(20, '=')
			<< "Program link status:\n" << log.data()
			<< std::string(20, '=') << std::endl;
	}

	for (const auto& s : shaders)
		gl::glDetachShader(m_programid, s.m_shaderid);

	gl::GLboolean result;
	gl::glGetProgrambv(m_programid, gl::GLenum::GL_LINK_STATUS, &result);
	if (result == gl::GL_FALSE)
		throw program_link_error();
}

program::program(program&& other)
	: m_programid(other.m_programid)
{
	other.m_programid = 0;
}

program& program::operator=(program&& other) {
	if (this != &other) {
		m_programid = other.m_programid;
		other.m_programid = 0;
	}
	return *this;
}

program::~program() {
	if (m_programid)
		gl::glDeleteProgram(m_programid);
}

bool program::use() const {
	if (m_programid) {
		gl::glUseProgram(m_programid);
		return true;
	}
	return false;
}

void program::matrix(const std::string& name, const glm::mat4& mat) {
	if (!use())
		return;

	auto it = m_uniforms.find(name);
	if (it == m_uniforms.end()) {
		gl::GLint location = gl::glGetUniformLocation(m_programid, name.c_str());
		if (location == -1)
			throw glerror();
		it = m_uniforms.insert({ name, location }).first;
	}
	glUniformMatrix4fv(it->second, 1, gl::GL_FALSE, glm::value_ptr(mat));
}


program_link_error::program_link_error()
	: runtime_error("Program linkage failed")
{}

}
