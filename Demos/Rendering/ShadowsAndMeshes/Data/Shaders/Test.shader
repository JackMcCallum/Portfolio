#shader VERTEX
// ========================================
// Vertex Shader
#version 330

in vec3 iPosition POSITION;
in vec3 iNormal NORMAL;
in vec2 iTexcoord TEXCOORD0;

out vec3 vPosition;
out vec3 vNormal;
out vec3 vVNormal;
out vec4 vShadow;
out vec2 vTexcoord;

uniform mat4 uProjViewMatrix;
uniform mat4 uShadowViewProjMatrix;
uniform mat4 uShadowViewMatrix;

void main()
{
	gl_Position = uProjViewMatrix * vec4(iPosition, 1);
	vPosition = iPosition;
	vNormal = iNormal;
	vVNormal = mat3(uShadowViewMatrix) * iNormal;
	vTexcoord = iTexcoord;
	vShadow = uShadowViewProjMatrix * vec4(iPosition + iNormal*0.05, 1);
}

#shader FRAGMENT
// ========================================
// Fragment Shader
#version 330

#include "../Test3.shader"

in vec3 vPosition;
in vec3 vNormal;
in vec3 vVNormal;
in vec4 vShadow;
in vec2 vTexcoord;

out vec4 oColor;

uniform vec3 uLightDirection;
uniform sampler2D uTexDiffuse;
uniform sampler2DShadow uTexShadow;
uniform vec3 uCameraPosition;

void main()
{
	vec3 ambient = mix(vec3(0.2,0.2,0.2), vec3(0.4,0.4,0.4), vec3(vNormal.y*0.5+0.5));
	vec3 L = normalize(uLightDirection);
	vec3 N = normalize(vNormal);
	float NdotL = dot(N, L);
	float depth = length(vPosition - uCameraPosition);
	float shadow = shadowFactor(uTexShadow, vShadow, vec2(4096), NdotL, 1);
	
	vec3 diffuse = vec3(1) * clamp(NdotL, 0, 1);
	vec3 subsurf = vec3(0.2) * clamp(1-NdotL, 0, 1);
	
	vec3 projCoords = (vShadow.xyz / vShadow.w)*0.5+0.5;
	//oColor = vec4(ambient + vec3(max(0, NdotL) * shadow), 1); // max(0, NdotL) + 
	oColor = vec4(ambient + diffuse * shadow, 1); // max(0, NdotL) + 
	oColor *= texture(uTexDiffuse, vTexcoord);
	
	//oColor = vec4(depth);
	
}



