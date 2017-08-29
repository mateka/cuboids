#pragma once

namespace cuboid {
/*! \brief String with cuboid vertex shader. */
const char* vertex = R"(

#version 430

layout(location = 0) in vec3 vpos;
layout(location = 1) in vec3 vcolor;
layout(location = 2) in mat4 model;


out vec3 color;

uniform mat4 pv;

void main() {
    gl_Position = pv * model * vec4(vpos, 1.0);
    color = vcolor;
}

)";

}
