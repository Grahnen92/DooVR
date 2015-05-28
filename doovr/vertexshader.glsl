#version 400
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexNormal;
layout(location = 2) in vec2 vertexUV;

out vec3 Position;
out vec3 Normal;
out vec2 UV;
out vec3 lPos;

uniform mat4 MV;
uniform mat4 P;
uniform vec3 lightPos;

//uniform mat3 NormalMatrix;
//uniform mat4 OMV;

void main () 
{	
	Position =  vec3( MV * vec4(VertexPosition, 1.0));
	Normal = normalize(mat3(MV) * VertexNormal);
	UV = vertexUV;
	lPos = lightPos;

	//! Convert position to clip coordinates and pass along to fragment shader
	gl_Position =  (P * MV) * vec4(VertexPosition, 1.0);

}