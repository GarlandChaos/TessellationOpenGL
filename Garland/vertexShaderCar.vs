#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
out vec3 rgbColor;
out vec3 Normal;
out vec3 NormalTESTE;
out vec3 FragPos;
out vec2 TexCoord;
uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 curvePos;
void main()
{
    FragPos = vec3(view  * transform * vec4(aPos + curvePos, 1.0));
	rgbColor = vec3(1.0f, 0.5f, 0.2f);
	Normal = aNormal;
	NormalTESTE = aNormal;
	TexCoord = aTexCoord;
	gl_Position = projection * view  * transform * vec4(aPos + curvePos, 1.0);
}