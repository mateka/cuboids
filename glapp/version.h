#pragma once

#include <cstdlib>
#include <iosfwd>


namespace glapp {

/*! \brief Class for storing version number. */
class version final {
public:
	/*! \brief Creates version.
	*   \param major major part of version.
	*   \param minor minor part of version.
	*   \param rev revision part of version (default: 0). */
	version(const std::size_t major, const std::size_t minor, const std::size_t rev = 0);

	version(version&&) = default;
	version(const version&) = default;
	version& operator=(version&&) = default;
	version& operator=(const version&) = default;

	/*! \brief Major part accessor.
	*   \return Version's major part. */
	std::size_t major() const;

	/*! \brief Minor part accessor.
	*   \return Version's minor part. */
	std::size_t minor() const;

	/*! \brief Rev part accessor.
	*   \return Version's rev part. */
	std::size_t rev() const;
private:
	std::size_t m_major;
	std::size_t m_minor;
	std::size_t m_rev;
};

/*! \brief Test for versions equality.
*   \param a first version to compare.
*   \param b second version to compare.
*   \return true, if all: major, minor and rev of given versions are equal. */
bool operator==(const version& a, const version& b);

/*! \brief Test for resolutions inequality.
*   \param a first version to compare.
*   \param b second version to compare.
*   \return false, if all: major, minor and rev of given versions are equal. */
bool operator!=(const version& a, const version& b);

/*! \brief Comparison.
*   \param a first version to compare.
*   \param b second version to compare.
*   \return true, if a version is lexicographically smaller than b. */
bool operator<(const version& a, const version& b);

/*! \brief Comparison.
*   \param a first version to compare.
*   \param b second version to compare.
*   \return true, if a version is lexicographically smaller or equal to b. */
bool operator<=(const version& a, const version& b);

/*! \brief Comparison.
*   \param a first version to compare.
*   \param b second version to compare.
*   \return true, if a version is lexicographically greater than b. */
bool operator>(const version& a, const version& b);

/*! \brief Comparison.
*   \param a first version to compare.
*   \param b second version to compare.
*   \return true, if a version is lexicographically greater or equal to b. */
bool operator>=(const version& a, const version& b);

/*! \brief Outputs version to output stream.
*  \param os output stream
*  \param v version
*  \return os stream with version v output to it.
*/
std::ostream& operator<<(std::ostream& os, const version& v);


}
