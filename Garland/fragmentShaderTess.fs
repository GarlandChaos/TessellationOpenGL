#version 410

in vec2 textureCoordinate;

out vec4 fragcolour;

uniform sampler2D texture1;
uniform sampler2D terrain;

void main () {
	fragcolour = texture(terrain, textureCoordinate);
}
