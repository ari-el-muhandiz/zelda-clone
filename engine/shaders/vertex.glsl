#version 330 core
layout (location = 0) in vec2 aPos;
uniform vec2 offset;
uniform float scale;
void main() {
    gl_Position = vec4((aPos * scale) + offset, 0.0, 1.0);
}
