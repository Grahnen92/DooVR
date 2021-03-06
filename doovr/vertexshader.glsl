#version 400
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexNormal;

out vec3 Position;
out vec3 Normal;

uniform mat4 MV;
uniform mat4 OMV;
uniform mat4 P;

//uniform mat3 NormalMatrix;


void main () 
{
	//mat3 NormalMatrix = inverse(transpose(mat3(MV)));
	
	// Eye coordinates
	Position =  vec3( MV * vec4(VertexPosition, 1.0));
	//Normal =  normalize(NormalMatrix * VertexNormal); //Ratt men blur

	//Normal = vec3( OMV * vec4(VertexNormal, 0.0));
	//Normal = normalize(mat3(MV) * VertexNormal);

	 //ny kod
	 //convert in world coords
	//Position = mat3(MV) * VertexPosition;			    //careful here
	Normal = normalize(mat3(MV) * VertexNormal);


	//! Convert position to clip coordinates and pass along to fragment shader
	gl_Position =  P * MV * vec4(VertexPosition, 1.0);

}