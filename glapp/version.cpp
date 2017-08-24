#include <glapp/version.h>
#include <iostream>
#include <tuple>


namespace glapp {

version::version(const std::size_t major, const std::size_t minor, const std::size_t rev)
	: m_major{ major }, m_minor{ minor }, m_rev{ rev }
{}


std::size_t version::major() const {
	return m_major;
}

std::size_t version::minor() const {
	return m_minor;
}

std::size_t version::rev() const {
	return m_rev;
}

bool operator==(const version& a, const version& b) {
	return a.major() == b.major() && a.minor() == b.minor() && a.rev() == b.rev();
}

bool operator!=(const version& a, const version& b) {
	return !(a == b);
}

bool operator<(const version& a, const version& b) {
	const auto lhs = std::make_tuple(a.major(), a.minor(), a.rev());
	const auto rhs = std::make_tuple(b.major(), b.minor(), b.rev());
	return lhs < rhs;
}

bool operator<=(const version& a, const version& b) {
	return !(b < a);
}

bool operator>(const version& a, const version& b) {
	return b < a;
}

bool operator>=(const version& a, const version& b) {
	return !(a < b);
}


std::ostream& operator<<(std::ostream& os, const version& v) {
	return os << v.major() << "." << v.minor() << "." << v.rev();
}


}
