#include <utils/cooldown_timer.h>


namespace utils {

cooldown_timer::cooldown_timer(const cooldown_timer::type cooldown)
    : m_cooldown{cooldown}, m_remaining{0}
{}

cooldown_timer::type cooldown_timer::cooldown() const {
    return m_cooldown;
}

cooldown_timer::type cooldown_timer::remaining() const {
    using namespace std::chrono;
    return m_remaining < 0ns ? 0ns : m_remaining;
}

cooldown_timer::operator bool() const {
    using namespace std::chrono;
    return remaining() <= 0ns;
}

void cooldown_timer::update(const cooldown_timer::type elapsed) {
    m_remaining -= elapsed;
}

std::ostream& operator<<(std::ostream& os, const cooldown_timer& t) {
	return os
        << t.cooldown().count() - t.remaining().count() << "/"
        << t.cooldown().count() << " [ns]";
}

}
