#version 330
in vec3 vPosition;

out float oColor;

void main()
{
	oColor = vPosition.z;
}