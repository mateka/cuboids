#pragma once

namespace pyramid {
/*! \brief String with pyramid geometry shader. */
const char* geometry = R"(

#version 430

layout(triangles) in;
in vec4 vertexColor[3];
in float vertexIntensity[3];

layout(triangle_strip, max_vertices = 3) out;
out vec4 fragmentColor;
out float fragmentIntensity;
out noperspective vec3 wireframeDistance;

void main()
{
	for(int  i = 0; i < 3; ++i) {
		gl_Position = gl_in[i].gl_Position;
		fragmentColor = vertexColor[i];
		fragmentIntensity = vertexIntensity[i];

		wireframeDistance = vec3(0, 0, 0);
		wireframeDistance[i] = 1;

		EmitVertex();
	}
    EndPrimitive();
}

)";

}
