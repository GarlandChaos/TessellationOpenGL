#version 410

layout (location = 0) in vec3 aPos;
layout ( location = 1 ) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 Pos;
out vec2 TexCoord;
out vec3 Normal;

void main() {

	Pos = aPos;
	TexCoord = aTexCoord; 
	Normal = aNormal;
}
