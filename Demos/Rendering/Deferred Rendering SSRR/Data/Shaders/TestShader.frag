#version 330
in vec3 vPosition;
in vec3 vNormal;
in vec4 vTangent;
in vec2 vTexcoord;

out vec4 oColor0;
out vec4 oColor1;
out vec4 oColor2;
out vec4 oColor3;

uniform vec3 cameraPosition;
uniform sampler2D testUniform;
uniform sampler2D testUniform2;
uniform vec3 lightPosition;

void phongLambertian(in vec3 N, in vec3 L, in vec3 E, in float roughness, float reflectance, out float diffuse, out float specular)
{
	float exponent = pow(1 / roughness, (1+reflectance)*4);
	vec3 H = normalize(L + E);
	diffuse = max(0.0f, dot(N, L));
	specular = pow(max(0.0f, dot(H, N)), exponent);
}

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
	//if (diffuseSamp.w < 0.5) discard;
	
	vec4 diffuseSamp = texture(testUniform2, vTexcoord);
	vec4 specularSamp = texture(testUniform2, vTexcoord);
	vec4 normSamp = texture(testUniform, vTexcoord);
	
	// Prepare the transform for the normal
	mat3 tbn;
	tbn[0] = normalize(vTangent.xyz);
	tbn[2] = normalize(vNormal);
	tbn[1] = cross(tbn[2], tbn[0]);
	tbn[1] *= vTangent.w;
	
	// Prepare the lighting components
	vec3 N = normalize(tbn * (normSamp.xyz*2-1));
	vec3 L = normalize(lightPosition - vPosition);
	vec3 E = normalize(cameraPosition - vPosition);
	
	// Calculate BRDF
	float D = 0, S = 0;
	orenNayarCookTorrance(N,L,E, 0.4, 0.5, D,S);
	
	// Calculate attenuation
	float A = pow(max(0, 1-(length(lightPosition - vPosition) / 32)), 2);
	
	// Compute ambient colour
	vec3 ambientColor = diffuseSamp.xyz * mix(vec3(0.1), vec3(0.2), N.y*0.5+0.5);
	vec3 diffuseColor = diffuseSamp.xyz * D * A;
	vec3 specularColor = diffuseSamp.xyz * S * A * 0.2;
	
	// Finalize
	oColor0 = vec4(N*0.5+0.5, 1);
	oColor1 = vec4(vPosition, 1);
	oColor2 = diffuseSamp;
	oColor3 = diffuseSamp;
}