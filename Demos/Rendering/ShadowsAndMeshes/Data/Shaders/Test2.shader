#shader VERTEX
// ========================================
// Vertex Shader
#version 330

in vec3 iPosition;
in vec3 iNormal;

out vec4 vProjection;

uniform mat4 uProjViewMatrix;

void main()
{
	gl_Position = uProjViewMatrix * vec4(iPosition, 1);
	vProjection = gl_Position;
}

#shader FRAGMENT
// ========================================
// Fragment Shader
#version 330

in vec4 vProjection;

out float oDepth;

void main()
{
	oDepth = (vProjection.z / vProjection.w) * 0.5+0.5;
}

