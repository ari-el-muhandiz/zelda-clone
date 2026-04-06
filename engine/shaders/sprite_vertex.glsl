#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;
uniform vec2 offset;
uniform float scale;
uniform vec2 uvOffset;
uniform vec2 uvScale;

out vec2 TexCoord;

void main()
{
    gl_Position = vec4((aPos * scale) + offset, 0.0, 1.0);
    TexCoord = uvOffset + (aTexCoord * uvScale);
}
