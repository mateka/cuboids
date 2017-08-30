#pragma once


namespace cuboidslib {

class moving_ship;
class bullet;
class rocket;
class cuboid;
class crate;
class explosion;

/*! \brief cuboids lib objects visitor interface. */
class ivisitor {
public:
	virtual ~ivisitor() {}

	/*! \brief Visits moving ship. */
	virtual void on_visit(const moving_ship&) = 0;

	/*! \brief Visits bullet. */
	virtual void on_visit(const bullet&) = 0;

	/*! \brief Visits rocket. */
	virtual void on_visit(const rocket&) = 0;

	/*! \brief Visits cuboid. */
	virtual void on_visit(const cuboid&) = 0;

	/*! \brief Visits crate. */
	virtual void on_visit(const crate&) = 0;

	/*! \brief Visits explosion. */
	virtual void on_visit(const explosion&) = 0;
};

}
