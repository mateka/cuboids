#pragma once

#include <cstdlib>
#include <iosfwd>


namespace glapp {

/*! \brief Class for storing OpenGL resolution. */
class resolution final {
public:
	/*! \brief Creates resolution pair.
	*   \param width window's width
	*   \param width window's height */
	resolution(const std::size_t width, const std::size_t height);

	resolution(resolution&&) = default;
	resolution(const resolution&) = default;
	resolution& operator=(resolution&&) = default;
	resolution& operator=(const resolution&) = default;

	/*! \brief Width accessor.
	*   \return Resolution's width. */
	std::size_t width() const;

	/*! \brief Height accessor.
	*   \return Resolution's height. */
	std::size_t height() const;
private:
	std::size_t m_width;
	std::size_t m_height;
};

/*! \brief Test for resolutions equality.
*   \param a first resolution to compare.
*   \param b second resolution to compare.
*   \return true, if both: width and height of given resolutions are equal. */
bool operator==(const resolution& a, const resolution& b);

/*! \brief Test for resolutions inequality.
*   \param a first resolution to compare.
*   \param b second resolution to compare.
*   \return false, if both: width and height of given resolutions are equal. */
bool operator!=(const resolution& a, const resolution& b);

/*! \brief Outputs resolution to output stream.
*  \param os output stream
*  \param r resolution
*  \return os stream with resolution r output to it.
*/
std::ostream& operator<<(std::ostream& os, const resolution& r);

}
