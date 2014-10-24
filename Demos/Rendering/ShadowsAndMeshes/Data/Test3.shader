const float DEPTH_BIAS = 0.001;
const int SHADOW_ITER = 2;
const int MAX_SHADOW_ITER = (SHADOW_ITER*2+1) * (SHADOW_ITER*2+1);

float shadowFactor(sampler2DShadow shadowtex, vec4 lightSpacePos, vec2 texSize, float NdotL, float spread)
{
    vec3 projCoords = (lightSpacePos.xyz / lightSpacePos.w)*0.5+0.5;
    vec2 invRes = (1.0f / texSize);
    
	float bias = clamp(tan(acos(NdotL)), 0, DEPTH_BIAS*2) + DEPTH_BIAS;
	float shadow = 0.0f;
	for (int y = -SHADOW_ITER ; y <= SHADOW_ITER ; y++)
	{
        for (int x = -SHADOW_ITER ; x <= SHADOW_ITER ; x++)
		{
			vec2 offset = vec2(x, y)*invRes;
			shadow += texture(shadowtex, vec3(projCoords.xy + offset, projCoords.z-bias));
		}
	}
	
	shadow /= MAX_SHADOW_ITER;
	float facingLight = sign(NdotL)*0.5+0.5;
	
    return 1-(1-shadow) * facingLight;
}
