#pragma once


namespace cuboidslib {

class moving_ship;
class bullet;
class cuboid;

/*! \brief cuboids lib objects visitor interface. */
class ivisitor {
public:
	virtual ~ivisitor() {}

	/*! \brief Visits moving ship. */
	virtual void on_visit(const moving_ship&) = 0;

	/*! \brief Visits bullet. */
	virtual void on_visit(const bullet&) = 0;

	/*! \brief Visits cuboid. */
	virtual void on_visit(const cuboid&) = 0;
};

}