#include <gllib/vbo.h>
#include <gllib/error.h>


namespace gllib {

vbo::vbo()
	: m_arrayid([]() {
		gl::GLuint arrayID;
		gl::glGenVertexArrays(1, &arrayID);
		return arrayID;
	}())
{
	if (!m_arrayid)
		throw glerror();
}

vbo::vbo(vbo&& other)
	: m_arrayid(other.m_arrayid)
{
	other.m_arrayid = 0;
}

vbo& vbo::operator=(vbo&& other) {
	if (this != &other) {
		m_arrayid = other.m_arrayid;
		other.m_arrayid = 0;
	}
	return *this;
}

vbo::~vbo() {
	if (m_arrayid)
		gl::glDeleteVertexArrays(1, &m_arrayid);
}

bool vbo::bind() const {
	if (m_arrayid) {
		gl::glBindVertexArray(m_arrayid);
		return true;
	}
	return false;
}

void vbo::enable_array(const gl::GLuint n) const {
	if (m_arrayid)
		gl::glEnableVertexArrayAttrib(m_arrayid, n);
}

void vbo::disable_array(const gl::GLuint n) const {
	if (m_arrayid)
		gl::glDisableVertexArrayAttrib(m_arrayid, n);
}

}
