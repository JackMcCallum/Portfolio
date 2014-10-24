
#version 330

in vec3 iPosition;
in vec3 iNormal;
in vec2 iTexcoord;

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
	vNormal = iNormal;
	vVNormal = mat3(uShadowViewMatrix) * iNormal;
	vTexcoord = iTexcoord;
	vShadow = uShadowViewProjMatrix * vec4(iPosition + iNormal*0.05, 1);
}

