#version 330
in vec3 vPosition;
in vec3 vNormal;
in vec3 vVNormal;
in vec4 vShadow;
in vec2 vTexcoord;

out vec4 oColor;

uniform vec3 uLightDirection;

uniform sampler2D uTexDiffuse;
uniform sampler2DShadow uTexShadow;

const float DEPTH_BIAS = 0.002;
const int SHADOW_ITER = 1;
const int MAX_SHADOW_ITER = (SHADOW_ITER*2+1) * (SHADOW_ITER*2+1);

float shadowFactor(sampler2DShadow shadowtex, vec4 lightSpacePos, float NdotL)
{
    vec3 projCoords = (lightSpacePos.xyz / lightSpacePos.w)*0.5+0.5;
    float invRes = 1.0f/512.0f;
    
	float bias = tan(acos(NdotL)) * DEPTH_BIAS;
	float shadow = 0.0f;
	for (int y = -SHADOW_ITER ; y <= SHADOW_ITER ; y++)
	{
        for (int x = -SHADOW_ITER ; x <= SHADOW_ITER ; x++)
		{
			vec2 offset = vec2(x, y)*invRes;
			shadow += texture(shadowtex, vec3(projCoords.xy + offset, projCoords.z-bias));
		}
	}
	
    return (shadow / MAX_SHADOW_ITER);
}

void main()
{
	float ambient = mix(0.3, 0.2, vNormal.z*0.5+0.5);
	vec3 L = normalize(uLightDirection);
	vec3 N = normalize(vNormal);
	float NdotL = dot(N, L);
	float shadow = shadowFactor(uTexShadow, vShadow, NdotL);
	
	
	
	oColor = vec4(vec3(ambient) + vec3(max(0, NdotL)) * shadow, 1);
	oColor *= texture(uTexDiffuse, vTexcoord);
}






