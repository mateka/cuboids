#pragma once

#include <cuboidslib/iprojectile.h>
#include <vector>
#include <memory>


namespace cuboidslib {
namespace jamming {

/*! \brief Jamming policy for gun, which do not jam. */
class no_jam {
public:
	/*! \brief Update object state.
	*   \param delta time from last update. */
	void update(const seconds delta);

	/*! \brief Updates policy state with shoot result.
	*   \param r shot result. */
	void on_shot(const std::vector<std::unique_ptr<iprojectile>>& r);

	/*! \brief Check if gun should still work.
	*   \return false, if player can shoot from this gun. */
	bool jammed() const;
};


/*! \brief Jamming policy for gun, which jam after firing some bullets. */
class ammo_count_jam {
public:
	/*! \brief Initializes policy with given ammo count.
	*   \param ammo number of shots after which gun should jam. */
	ammo_count_jam(const std::size_t ammo);

	/*! \brief Update object state.
	*   \param delta time from last update. */
	void update(const seconds delta);

	/*! \brief Updates policy state with shoot result.
	*   \param r shot result. */
	void on_shot(const std::vector<std::unique_ptr<iprojectile>>& r);

	/*! \brief Check if gun should still work.
	*   \return false, if player can shoot from this gun. */
	bool jammed() const;
private:
	std::size_t m_ammo;
};

}
}
