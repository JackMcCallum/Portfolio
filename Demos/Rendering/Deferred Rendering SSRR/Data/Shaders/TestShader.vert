
#version 330

in vec3 iPosition;
in vec3 iNormal;
in vec4 iTangent;
in vec2 iTexcoord;

out vec3 vPosition;
out vec3 vNormal;
out vec4 vTangent;
out vec2 vTexcoord;

uniform mat4 pvmMatrix;
uniform mat4 modelMatrix;

void main()
{
	gl_Position = pvmMatrix * modelMatrix * vec4(iPosition, 1);
	vPosition = (modelMatrix * vec4(iPosition, 1)).xyz;
	vNormal = (modelMatrix * vec4(iNormal, 0)).xyz;
	vTexcoord = iTexcoord;
	vTangent = iTangent;
}

