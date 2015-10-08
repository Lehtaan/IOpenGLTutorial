#version 410 core

in vec2 position;
in vec2 texcoord;

in vec3 color;

out vec3 Color;
out vec2 Texcoord;

uniform float ratio;
uniform mat4 trans;
uniform vec3 pos;

void main() {
    Color = color;
    Texcoord = texcoord;
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0) + (trans * vec4(position.x, (position.y) * ratio, 0.0, 1.0));
}