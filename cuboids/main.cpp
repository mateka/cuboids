#include <iostream>
#include <stdexcept>
#include <glapp/app.h>
#include <gllib/gl.h>
//#include "moving_ship_painter.h"


class myapp : public glapp::app {
protected:
	using app::app;

    void update(const seconds delta) override {
		//painter.update(delta);
		//painter.draw();
        std::cout << "FPS: " << 1.0 / delta.count() << "." <<std::endl;
    }

	//glcuboids::moving_ship_painter painter;
};

int main(int argc, char* argv[]) {
    try
    {
		myapp::params_type params;
		myapp a{
			myapp::params_type()
			.set_glversion(glapp::version{4, 3})
			.set_resolution(glapp::resolution{800, 600})
		};
		std::cout << "OpenGL version: " << a.glversion() << std::endl;
		gl::glClearColor(0, 0, 0.5f, 1.0f);
        a.run();
    }
    catch(const std::exception& ex) {
        std::cerr << "ERROR: " << ex.what() <<std::endl;
        return 1;
    }
}
