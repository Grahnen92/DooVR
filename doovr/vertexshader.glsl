#version 400
layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;

uniform mat4 MV;
uniform mat4 P;

out vec3 interpolatedColor;
out vec3 interpolatedNormal;


void main () 
{


	gl_Position = P * MV * vec4 (Position, 1.0);
	interpolatedNormal = mat3(MV) * Normal;
	
	interpolatedColor = vec3(1.0, 1.0, 1.0);
    
}