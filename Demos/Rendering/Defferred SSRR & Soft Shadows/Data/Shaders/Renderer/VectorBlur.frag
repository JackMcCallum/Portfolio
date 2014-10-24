#version 330
in vec2 vPosition;
out vec4 oColor;

uniform sampler2D uTexNormals;
uniform sampler2D uTexDiffuse;
uniform sampler2D uTexSpecular;
uniform sampler2D uTexDepth;



void main()
{
	float zNear = 0.1;
	float zFar = 128;
	
	float z_b = texture2D(uTexDepth, vPosition*0.5+0.5).x;
    float z_n = 2.0 * z_b - 1.0;
    float z_e = 2.0 * zNear * zFar / (zFar + zNear - z_n * (zFar - zNear));
	z_e *= 0.1;
	oColor = vec4(z_e,z_e,z_e,1);
}