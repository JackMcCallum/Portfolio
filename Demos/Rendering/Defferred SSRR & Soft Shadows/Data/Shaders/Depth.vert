
#version 330

in vec3 iPosition;
in vec3 iNormal;

out vec3 vPosition;

uniform mat4 uProjViewMatrix;

void main()
{
	gl_Position = uProjViewMatrix * vec4(iPosition, 1);
	vPosition = gl_Position.xyz;
}

