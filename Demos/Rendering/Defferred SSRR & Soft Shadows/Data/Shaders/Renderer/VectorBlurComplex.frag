#version 330
in vec2 vPosition;
in vec2 vTexCoord;
out vec4 oColor;

uniform sampler2D uTexSource;

// blur horizontal / blur vertical / inverse resolution x / inverse resolution y
uniform vec4 uBlurParams;

const int SAMPLES = 8;

void main()
{
	vec4 color = vec4(0);
	float t = 0;
	for (int i = -SAMPLES; i < SAMPLES; i++)
	{
		float f = 1-(abs(i) / float(SAMPLES));
		f *= f;
		t += f;
		color += texture(uTexSource, vTexCoord + uBlurParams.xy*uBlurParams.zw*i) * f;
	}
	color /= t;
	
	oColor = color;
}