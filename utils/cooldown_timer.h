#pragma once

#include <chrono>
#include <iostream>


namespace utils {

/*! \brief Class for timer counting down to 0.
 */
class cooldown_timer final {
public:
    using type = std::chrono::nanoseconds;    //!< Type of period

    /*! \brief Creates timer with given cooldown time.
    *   Newly created timer allows immediate execution.
	*   \param cooldown cooldown period.
    */
    cooldown_timer(const type cooldown);

    /*! \brief Cooldown accessor.
    *   \return Cooldown duration of this timer.
    */
    type cooldown() const;

    /*! \brief Remaining accessor.
    *   \return Remaining cooldown duration.
    */
    type remaining() const;

    /*! \brief Casting to bool - test whether cooldown time
    *   has passed.
    *   \return true if cooldown time has passed
    *   and guarded operations can be executed.
    */
    explicit operator bool() const;

    /*! \brief Update timer state.
    *   \param elapsed how much time elapsed since last update
    */
    void update(const type elapsed);

    /*! \brief Executes given action, if time elapsed since last
    *   execution is greater than cooldown time.
    *   \param act callable action to execute
    *   \return true if action was executed
    */
    template<typename Action>
    bool execute(Action act) {
        if(*this) {
            act();
            m_remaining = m_cooldown;
            return true;
        }
        return false;
    }
private:
    const type m_cooldown;
    type m_remaining;
};

/*! \brief Outputs cooldown to output stream.
*  \param os output stream
*  \param t cooldown timer
*  \return os stream with cooldown timer t output to it.
*/
std::ostream& operator<<(std::ostream& os, const cooldown_timer& t);

}
