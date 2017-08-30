#pragma once

#include <cuboidslib/cuboid.h>
#include <cuboidslib/iprojectile_factory.h>


namespace cuboidslib {

/*! \brief All models of fancy guns. */
enum class gun_model {
	wingman, //!< two guns on wings
	spray3,	//!< spray gun shoting 3 bullets
	spray5,	//!< spray gun shoting 5 bullets
	bazooka, //!< rocket launcher
	patriots, //!< two rocket launchers on wings
	boombastic3	//!< spray gun shoting 3 rockets
};

/*! \brief Crate object */
class crate : public cuboid {
public:
	/*! \brief Creates crate with random gun in it.
	*   \param w physics world in which crate will be registered.
	*   \param pos starting position of the crate.
	*   \param velocity linear velocity of the crate.
	*   \param rotation angular velocity of the crate.
	*   \param model nmber of gun, to store. */
	crate(
		physicslib::world& w,
		const glm::vec3& pos,
		const glm::vec3& velocity,
		const glm::vec3& rotation,
		const gun_model model
	);

	/*! \brief visitor pattern - visiting this object.
	*   \param v visitor object.*/
	void visit(imutable_visitor& v) override;

	/*! \brief visitor pattern - visiting this object.
	*   \param v visitor object.*/
	void visit(ivisitor& v) const override;

	/*! \brief Gives gun stored in this crate.
	*   \return Owning pointer to gun stored in this crate. */
	std::unique_ptr<iprojectile_factory> gun();
private:
	gun_model m_gun;
};

}
