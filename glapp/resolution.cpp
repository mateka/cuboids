#include <glapp/resolution.h>
#include <iostream>


namespace glapp {

resolution::resolution(const std::size_t width, const std::size_t height)
	: m_width{ width }, m_height{ height }
{}

std::size_t resolution::width() const {
	return m_width;
}

std::size_t resolution::height() const {
	return m_height;
}

bool operator==(const resolution& a, const resolution& b) {
	return a.width() == b.width() && a.height() == b.height();
}

bool operator!=(const resolution& a, const resolution& b) {
	return !(a == b);
}

std::ostream& operator<<(std::ostream& os, const resolution& r) {
	return os << r.width() << "x" << r.height();
}

}
