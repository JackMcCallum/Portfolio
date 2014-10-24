#version 330
in vec2 vPosition;
in vec2 vTexCoord;
out vec4 oColor;

uniform sampler2D uTexSource;

uniform vec4 uBloomParams;

void main()
{
	vec4 samp = texture(uTexSource, vTexCoord);
	
	oColor = max(vec4(0), samp-1)*10;
}