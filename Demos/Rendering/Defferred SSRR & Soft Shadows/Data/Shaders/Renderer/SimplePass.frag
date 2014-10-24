#version 330
in vec2 vPosition;
in vec2 vTexCoord;
out vec4 oColor;

uniform sampler2D uTexNormals;
uniform sampler2D uTexWorld;
uniform sampler2D uTexDiffuse;
uniform sampler2D uTexSource;

void main()
{
	vec4 refl = texture(uTexWorld, vTexCoord);
	vec3 lit = texture(uTexSource, vTexCoord).xyz*0.8;
	vec3 glow = texture(uTexNormals, vTexCoord).xyz;
	
	
	
	
	oColor = vec4(mix(lit, refl.xyz, refl.w), 1);
	//oColor = vec4(vec3(edgeFalloff(vTexCoord)), 1);
	//oColor = vec4(refl.xyz, 1);
}
