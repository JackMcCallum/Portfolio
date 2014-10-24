#version 330
in vec2 vPosition;
in vec2 vTexCoord;
out vec4 oColor;

uniform sampler2D uTexNormals;
uniform sampler2D uTexWorld;
uniform sampler2D uTexDiffuse;
uniform sampler2D uTexSpecular;

uniform vec3 uLightDirection;
uniform vec3 uLightColour;
uniform vec3 uCameraPosition;

void orenNayarCookTorrance(in vec3 N, in vec3 L, in vec3 E, in float roughness, float reflectance, out float diffuse, out float specular)
{
	float R2 = roughness * roughness; 
	vec3 H = normalize(L + E);
	
	float NdL = max(0.0f, dot(N, L)); 
	float NdE = max(0.0f, dot(N, E)); 
	float NdH = max(0.0f, dot(N, H)); 
	float HdE = dot(H, E);
	float NdH2 = NdH * NdH; 
	
	// Oren-Nayar
	float A = 1.0f - 0.5f * R2 / (R2 + 0.33f); 
	float B = 0.45f * R2 / (R2 + 0.09f);
	vec3 lightProjected = normalize(L - N * NdL); 
	vec3 viewProjected = normalize(E - N * NdE); 
	float CX = max(0.0f, dot(lightProjected, viewProjected));
	float alpha = sin(max(acos(NdE), acos(NdL))); 
	float beta = tan(min(acos(NdE), acos(NdL))); 
	float DX = alpha * beta;
	diffuse = NdL * (A + B * CX * DX);
	
	// Cook Torrance
	const float e = 2.71828182845904523536028747135f; 
	const float pi = 3.1415926535897932384626433832f; 
	float exponent = -(1 - NdH2) / (NdH2 * R2);
	float D = pow(e, exponent) / (R2 * NdH2 * NdH2);
	float F = mix(pow(1 - HdE, 5), 1, reflectance); 
	float X = 2.0f * NdH / dot(E, H); 
	float G = min(1, min(X * NdL, X * NdE));
	specular = max((D*G*F) / (NdE * pi), 0.0f);
}

void main()
{
	vec4 diffSamp = texture(uTexDiffuse, vTexCoord);
	vec4 specSamp = texture(uTexSpecular, vTexCoord);
	
	vec3 worldPos = texture(uTexWorld, vTexCoord).xyz;
	vec3 L = normalize(uLightDirection);
	vec3 N = texture(uTexNormals, vTexCoord).xyz*2-1;
	vec3 E = normalize(uCameraPosition - worldPos);
	
	float D, S;
	orenNayarCookTorrance(N, L, E, 0.3, 0.5, D, S);
	
	oColor = vec4(vec3(D+S)*uLightColour,0) * diffSamp;
}