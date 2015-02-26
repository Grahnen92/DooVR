#version 400
layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;

uniform mat4 MV;
uniform mat4 P;

out vec3 interpolatedColor;
out vec3 interpolatedNormal;


void main () 
{
    // Ambient, diffuse and specular constants. nS is a notation on shininess (higher = more shiny)
	float kA = 0.3;
	float kS = 0.4;
	float kD = 0.5;
	float nS = 4;

	gl_Position = P * MV * vec4 (Position, 1.0);
	interpolatedNormal = mat3(MV) * Normal;
	
	interpolatedColor = kA *vec3(1.0, 1.0, 1.0);
    
}