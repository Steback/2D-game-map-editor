#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main() {
    TexCoord = textureCoord;

    gl_Position = projection * view * model * vec4(position, 1.0);
}