#version 330
in vec2 vPosition;
in vec2 vTexCoord;
out vec4 oColor;

uniform sampler2D uTexSource;

// blur horizontal / blur vertical / inverse resolution x / inverse resolution y
uniform vec4 uBlurParams;

const int SAMPLES = 3;

void main()
{
	vec4 color = vec4(0);
	for (int i =- SAMPLES; i < SAMPLES; i++)
		color += texture(uTexSource, vTexCoord + uBlurParams.xy*uBlurParams.zw*i);
	color /= SAMPLES*2;
	
	oColor = color;
}