#pragma once

namespace pyramid {
/*! \brief String with pyramid fragment shader. */
const char* fragment = R"(

#version 430

in vec4 fragmentColor;
in float fragmentIntensity;
in noperspective vec3 wireframeDistance;

out vec4 endColor;

void main() {
    vec4 color = fragmentIntensity * fragmentColor;

    vec3 d = fwidth(wireframeDistance);
    vec3 a3 = smoothstep(vec3(0.0), d * 1.5, wireframeDistance);
    float edgeFactor = min(min(a3.x, a3.y), a3.z);
    endColor = mix(color, vec4(0, 0, 0, 0), edgeFactor);
}

)";

}
