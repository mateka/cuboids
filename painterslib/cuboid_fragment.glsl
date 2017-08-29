#pragma once

namespace cuboid {
/*! \brief String with cuboid fragment shader. */
const char* fragment = R"(

#version 430

in vec3 color;

out vec3 ocolor;

void main() {
    ocolor = color;
}

)";

}
