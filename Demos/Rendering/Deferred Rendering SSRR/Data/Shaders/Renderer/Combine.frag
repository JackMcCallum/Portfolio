#version 330
in vec2 vPosition;
in vec2 vTexCoord;
out vec4 oColor;

uniform sampler2D uTexNormals;
uniform sampler2D uTexWorld;
uniform sampler2D uTexDiffuse;
uniform sampler2D uTexSpecular;

void main()
{
	vec3 L = normalize(-texture(uTexWorld, vTexCoord).xyz);
	vec3 N = normalize(texture(uTexNormals, vTexCoord).xyz*2-1);
	
	float NdotL = dot(N, L);
	float D = mix(max(0, NdotL), NdotL*0.5+0.5, 0.3);
	
	oColor = vec4(vec3(D),1);
}