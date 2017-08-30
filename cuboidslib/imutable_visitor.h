#pragma once


namespace cuboidslib {

class moving_ship;
class bullet;
class cuboid;
class crate;

/*! \brief cuboids lib mutable objects visitor interface. */
class imutable_visitor {
public:
	virtual ~imutable_visitor() {}

	/*! \brief Visits moving ship. */
	virtual void on_visit(moving_ship&) = 0;

	/*! \brief Visits bullet. */
	virtual void on_visit(bullet&) = 0;

	/*! \brief Visits cuboid. */
	virtual void on_visit(cuboid&) = 0;

	/*! \brief Visits crate. */
	virtual void on_visit(crate&) = 0;
};

}