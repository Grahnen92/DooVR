#version 400
layout(location = 0) in vec3 Position;
//layout(location = 1) in vec3 Normal;

uniform mat4 MV;
uniform mat4 OMV;
uniform mat4 P;
uniform vec4 lightPos;

out vec3 interpolatedColor;
out vec3 interpolatedNormal;
out vec3 pos;
out vec3 lPos;


void main () 
{
	vec3 Normal = vec3( 1.0, 1.0, 1.0);

	gl_Position =  P * MV * vec4 (Position, 1.0);
	
	vec4 pos4 = MV * vec4 (Position, 1.0);
	
	pos = vec3(pos4) / pos4.w;
	lPos = vec3(lightPos);

	//interpolatedNormal = vec3( MV * vec4(Normal, 0.0));
	interpolatedNormal =  Normal;
	
	interpolatedColor = vec3(1.0, 1.0, 1.0);
    
}