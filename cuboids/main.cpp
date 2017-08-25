#include <iostream>
#include <cuboids/cuboids_glapp.h>

using namespace cuboids;

int main(int argc, char* argv[]) {
    try
    {
		cuboids_glapp::params_type params;
		cuboids_glapp app{
			cuboids_glapp::params_type()
			.set_glversion(glapp::version{4, 3})
			.set_resolution(glapp::resolution{800, 600})
		};
		app.run();
    }
    catch(const std::exception& ex) {
        std::cerr << "ERROR: " << ex.what() <<std::endl;
        return 1;
    }
}
