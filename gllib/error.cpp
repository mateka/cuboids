#include <gllib/error.h>
#include <gllib/gl.h>


namespace gllib {

namespace {

const char* glerror_text() {
	switch (gl::glGetError()) {
	case gl::GLenum::GL_NO_ERROR:
		return "GL_NO_ERROR";
	case gl::GLenum::GL_INVALID_ENUM:
		return "GL_INVALID_ENUM";
	case gl::GLenum::GL_INVALID_VALUE:
		return "GL_INVALID_VALUE";
	case gl::GLenum::GL_INVALID_OPERATION:
		return "GL_INVALID_OPERATION";
	case gl::GLenum::GL_INVALID_FRAMEBUFFER_OPERATION:
		return "GL_INVALID_FRAMEBUFFER_OPERATION";
	case gl::GLenum::GL_OUT_OF_MEMORY:
		return "GL_OUT_OF_MEMORY";
	default:
		return "Unknown OpenGL error";
	}
}

}

glerror::glerror()
	: runtime_error{ glerror_text() }
{}

}
