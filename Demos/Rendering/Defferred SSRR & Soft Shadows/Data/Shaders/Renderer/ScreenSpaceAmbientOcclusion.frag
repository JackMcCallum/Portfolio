#version 330
in vec2 vPosition;
in vec2 vTexCoord;
out vec4 oColor;

uniform sampler2D uTexNormals;
uniform sampler2D uTexWorld;
uniform sampler2D uTexNoise;

uniform vec3 uCameraPosition;

const int samples = 16;
const vec3 sphereSamples[samples] = vec3[](
      vec3( 0.5381, 0.1856,-0.4319), vec3( 0.1379, 0.2486, 0.4430),
      vec3( 0.3371, 0.5679,-0.0057), vec3(-0.6999,-0.0451,-0.0019),
      vec3( 0.0689,-0.1598,-0.8547), vec3( 0.0560, 0.0069,-0.1843),
      vec3(-0.0146, 0.1402, 0.0762), vec3( 0.0100,-0.1924,-0.0344),
      vec3(-0.3577,-0.5301,-0.4358), vec3(-0.3169, 0.1063, 0.0158),
      vec3( 0.0103,-0.5869, 0.0046), vec3(-0.0897,-0.4940, 0.3287),
      vec3( 0.7119,-0.0154,-0.0918), vec3(-0.0533, 0.0596,-0.5411),
      vec3( 0.0352,-0.0631, 0.5460), vec3(-0.4776, 0.2847,-0.0271)
);


void main()
{
	vec3 worldPos = texture(uTexWorld, vTexCoord).xyz;
	vec3 currNorm = texture(uTexNormals, vTexCoord).xyz*2-1;
	vec3 randomNorm = normalize(texture(uTexNoise, vTexCoord*vec2(1.6,1)*4).xyz*2-1);
	float depth = length(worldPos - uCameraPosition);
	
	float radius = 1.0f / depth;
	
	float ao = 0.0f;
	for (int i = 0; i < 16; ++i)
	{
		vec2 newOffset = reflect(sphereSamples[i], randomNorm).xy;
		
		vec2 offset1 = newOffset * radius*0.5;
		
		vec3 diff = texture(uTexWorld, vTexCoord + offset1).xyz - worldPos;
		vec3 v = normalize(diff);
		float d = length(diff)*8;
		
		ao += max(0.0f, dot(currNorm, v)-0.1) * (1.0f / (1.0f + d));
	}
	ao /= 16;
	ao = pow(1-ao, 8);
	oColor = vec4(vec3(ao), 1);
}