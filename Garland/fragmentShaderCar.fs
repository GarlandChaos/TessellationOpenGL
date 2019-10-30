#version 330 core
out vec4 FragColor;
in vec3 rgbColor;
in vec3 Normal;
in vec3 NormalTESTE;
in vec3 FragPos;
in vec2 TexCoord;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform sampler2D texture1;
uniform vec3 viewPos;
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float Ns;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (diff * Kd) * lightColor;

	vec3 ambient = Ka * lightColor;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), Ns);
	vec3 specular = lightColor * (spec * Ks);

    vec3 result = ambient + diffuse + specular;
    FragColor =  texture(texture1, TexCoord) * vec4(result, 1.0);
}