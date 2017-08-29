#pragma once

namespace cuboid {
/*! \brief String with cuboid fragment shader. */
const char* fragment = R"(

#version 430

in vec3 fragmentColor;
in noperspective vec3 wireframeDistance;

out vec4 endColor;

void main() {
    vec3 d = fwidth(wireframeDistance);
    vec3 a3 = smoothstep(vec3(0.0), d * 1.5, wireframeDistance);
    float edgeFactor = min(min(a3.x, a3.y), a3.z);
    endColor = mix(vec4(fragmentColor, 1), vec4(0, 0, 0, 0), edgeFactor);
}

)";

}
