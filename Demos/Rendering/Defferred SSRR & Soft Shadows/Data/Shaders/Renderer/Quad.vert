#version 330

in vec3 iPosition;
out vec2 vPosition;
out vec2 vTexCoord;

void main()
{
	gl_Position = vec4(iPosition, 1);
	vPosition = iPosition.xy;
	vTexCoord = iPosition.xy*0.5+0.5;
}

