#version 400
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexNormal;
layout(location = 2) in vec2 vertexUV;

out vec3 Position;
out vec3 Normal;
out vec2 UV;

uniform mat4 MV;
uniform mat4 P;

//uniform mat3 NormalMatrix;
//uniform mat4 OMV;

void main () 
{
	//mat3 NormalMatrix = inverse(transpose(mat3(MV)));
	//Normal =  normalize(NormalMatrix * VertexNormal); //Ratt men blur
	//Normal = vec3( OMV * vec4(VertexNormal, 0.0));
	//Position = mat3(MV) * VertexPosition;			    //careful here
	
	
	Position =  vec3( MV * vec4(VertexPosition, 1.0));
	Normal = normalize(mat3(MV) * VertexNormal);
	UV = vertexUV;

	//! Convert position to clip coordinates and pass along to fragment shader
	gl_Position =  (P * MV) * vec4(VertexPosition, 1.0);

}