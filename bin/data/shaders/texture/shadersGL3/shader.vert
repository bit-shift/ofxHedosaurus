#version 150

// these are for the programmable pipeline system and are passed in
// by default from OpenFrameworks
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec2 texcoord;

out vec2 texCoordVarying;
out vec3 pos;

// this is coming from our C++ code
uniform float mouseX;

void main(void)
{
    pos = gl_Vertex.xyz;
    gl_Position = ftransform();
}