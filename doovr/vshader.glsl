#version 400
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexNormal;

out vec3 Position;
out vec3 Normal;
out vec3 LP;

uniform mat4 MV;
uniform mat4 P;
uniform vec3 LP1;

void main () 
{
	Position =  vec3( MV * vec4(VertexPosition, 1.0));
	Normal = normalize(mat3(MV) * VertexNormal);
	LP = LP1;
	//! Convert position to clip coordinates and pass along to fragment shader
	gl_Position =  (P * MV) * vec4(VertexPosition, 1.0);

}