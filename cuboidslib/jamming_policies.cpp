#include <cuboidslib/jamming_policies.h>


namespace cuboidslib {
namespace jamming {

void no_jam::update(const seconds delta)
{}

void no_jam::on_shot(const std::vector<std::unique_ptr<iprojectile>>& r)
{}

bool no_jam::jammed() const {
	return false;
}


ammo_count_jam::ammo_count_jam(const std::size_t ammo)
	: m_ammo{ ammo }
{}

void ammo_count_jam::update(const seconds delta)
{}

void ammo_count_jam::on_shot(const std::vector<std::unique_ptr<iprojectile>>& r)
{
	if (r.size() > 0)
		--m_ammo;
}

bool ammo_count_jam::jammed() const {
	return m_ammo == 0;
}

}
}
