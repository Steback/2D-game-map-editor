#version 330

in vec2 TexCoord;

out vec4 outColor;

uniform sampler2D Tex;

void main() {
    outColor = texture(Tex, TexCoord);
}