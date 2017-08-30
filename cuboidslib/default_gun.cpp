#include <cuboidslib/default_gun.h>
#include <physicslib/world.h>
#include <cuboidslib/bullet.h>


using namespace std::chrono_literals;

namespace cuboidslib {

default_gun::default_gun(const seconds& cooldown)
	: launcher{ cooldown, glm::vec3{ 0, 0, -5.0f }, 2s, 1.0f, jamming_policy{} }
{}

}
