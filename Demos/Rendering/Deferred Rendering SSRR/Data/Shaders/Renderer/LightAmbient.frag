#version 330
in vec2 vPosition;
in vec2 vTexCoord;
out vec4 oColor;

uniform sampler2D uTexNormals;
uniform sampler2D uTexDiffuse;
uniform sampler2D uTexSSAO;

uniform vec3 uAmbientColorLower;
uniform vec3 uAmbientColorUpper;

void main()
{
	vec3 normSamp = texture(uTexNormals, vTexCoord).xyz*2-1;
	vec3 finalAmbi = mix(uAmbientColorLower, uAmbientColorUpper, normSamp.y*0.5+0.5);
	oColor = texture(uTexSSAO, vTexCoord) * texture(uTexDiffuse, vTexCoord) * vec4(finalAmbi, 1);
}