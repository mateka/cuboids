#pragma once


namespace cuboidslib {

class moving_ship;

/*! \brief cuboids lib objects visitor interface. */
class ivisitor {
public:
	virtual ~ivisitor() {}

	/*! \brief Visits moving ship. */
	virtual void on_visit(const moving_ship&) = 0;
};

}
