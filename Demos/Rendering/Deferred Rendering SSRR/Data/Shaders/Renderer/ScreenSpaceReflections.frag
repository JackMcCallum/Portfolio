#version 330
in vec2 vPosition;
in vec2 vTexCoord;
out vec4 oColor;

uniform sampler2D uTexNormals;
uniform sampler2D uTexWorld;
uniform sampler2D uTexDiffuse;
uniform sampler2D uTexSource;

uniform vec3 uCameraPosition;
uniform mat4 uViewMatrix;

const int NUM_SAMPLES = 32;
const float SAMPLE_SPACING = 0.5f;
const float SAMPLE_TOLLERANCE = 2.5f;

float edgeFalloff(vec2 uv)
{
	vec2 s = pow(abs(uv*2-1), vec2(6,4));
	return 1-max(0, min(1, s.x+s.y));
}

void main()
{
	vec3 normal = texture(uTexNormals, vTexCoord).xyz*2-1;
	vec3 world = texture(uTexWorld, vTexCoord).xyz;
	vec3 eye = normalize(uCameraPosition - world);
	vec3 ray = reflect(-eye, normal);
	
	float fresnel = pow(1-max(0, dot(eye, normal)), 2);
	
	
	vec3 col = vec3(0);
	float bt = 0;
	for (int i=0; i<NUM_SAMPLES; i++)
	{
		// Pick a point on the ray
		vec3 raysamp = world + ray*(i+1)*SAMPLE_SPACING;
		
		// Put ray into screenspace
		vec4 vssamp = uViewMatrix * vec4(raysamp, 1);
		vssamp /= vssamp.w; // Now its between -1 and 1
		vssamp = vssamp*0.5+0.5; // Now its between 0 and 1
		
		vec3 p = texture(uTexWorld, vssamp.xy).xyz;
		vec3 c = texture(uTexSource, vssamp.xy).xyz * edgeFalloff(vssamp.xy);
		
		float b = max(0, 0.5-length(raysamp-p)/SAMPLE_TOLLERANCE);
		col += c * b;
	}
	
	
	float roughness = texture(uTexDiffuse, vTexCoord).w;
	oColor = vec4(col, 0.3*fresnel);
}

/*
	
*/






