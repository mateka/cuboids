#pragma once

namespace pyramid {
/*! \brief String with pyramid fragment shader. */
const char* vertex = R"(

#version 430

layout(location = 0) in vec3 vpos;
layout(location = 1) in vec3 vcolor;
layout(location = 2) in mat4 model;
layout(location = 2) in float colorIntensity;


out vec3 color;
out float intensity;

uniform mat4 pv;

void main() {
    gl_Position = pv * model * vec4(vpos, 1.0);
    color = vcolor;
	intensity = 1.0f;
}

)";

}
