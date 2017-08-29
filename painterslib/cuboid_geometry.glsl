#pragma once

namespace cuboid {
/*! \brief String with cuboid geometry shader. */
const char* geometry = R"(

#version 430

layout(triangles) in;
in vec3 vertexColor[3];

layout(triangle_strip, max_vertices = 3) out;
out vec3 fragmentColor;
out noperspective vec3 wireframeDistance;

void main()
{
	for(int  i = 0; i < 3; ++i) {
		gl_Position = gl_in[i].gl_Position;
		fragmentColor = vertexColor[i];

		wireframeDistance = vec3(0, 0, 0);
		wireframeDistance[i] = 1;

		EmitVertex();
	}
    EndPrimitive();
}

)";

}
