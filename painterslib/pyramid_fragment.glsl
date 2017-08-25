#pragma once

namespace pyramid {
/*! \brief String with pyramid fragment shader. */
const char* fragment = R"(

#version 430

in vec3 color;
in float intensity;

out vec3 ocolor;

void main() {
    ocolor = intensity * color;
}

)";

}
