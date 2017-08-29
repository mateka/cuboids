#pragma once

namespace pyramid {
/*! \brief String with pyramid vertex shader. */
const char* vertex = R"(

#version 430

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in mat4 model;
layout(location = 6) in float inIntensity;

out vec3 vertexColor;
out float vertexIntensity;

uniform mat4 pv;

void main() {
    gl_Position = pv * model * vec4(inPosition, 1.0);
    vertexColor = inColor;
	vertexIntensity = inIntensity;
}

)";

}
