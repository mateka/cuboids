#include <glapp/app.h>
#include <utils/gl.h>


namespace glapp {

app::app(const app::params_type& params)
	: m_window(params)
{}

version app::glversion() const {
	return m_window.glversion();
}

int app::get_key(const int key) const {
	return m_window.get_key(key);
}

void app::run() {
    using namespace std::chrono;

    high_resolution_clock::time_point last;
    while (!m_window.should_close() )
    {
        auto now = high_resolution_clock::now();
        if(now - last == 0ns)
            continue;
        
		gl::glClear(
			gl::ClearBufferMask::GL_COLOR_BUFFER_BIT |
			gl::ClearBufferMask::GL_DEPTH_BUFFER_BIT
		);
        update(now - last);
        m_window.present();

        last = now;
    }
}

}
