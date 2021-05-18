#version 330 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPos;

/*
struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
*/

out vec4 FragColor;

uniform sampler2D texture_diffuse1;

//uniform Light light;

//uniform vec3 viewPos;

void main()
{	
	/*
	vec3 ambient	= light.ambient * texture(texture_diffuse1, TexCoords).rgb;
	
	vec3 norm 		= normalize(Normal);
	vec3 lightDir	= normalize(light.position - FragPos);
	float diff		= max(dot(norm, lightDir), 0.0);
	vec3 diffuse	= diff * light.diffuse * texture(texture_diffuse1, TexCoords).rgb;
	
	vec3 viewDir	= normalize(viewPos - FragPos);
	vec3 reflectDir	= reflect(-lightDir, norm);
	float spec		= pow(max(dot(viewDir, reflectDir), 0.0), 16);
	vec3 specular	= spec * light.specular * texture(texture_diffuse1, TexCoords).rgb;
	
	vec3 result		= (ambient + diffuse + specular);
	FragColor		= vec4(result, 1.0);
	*/
	
	vec3 color		= texture(texture_diffuse1, TexCoords).rgb;
	FragColor		= vec4(color, 1.0f);
}