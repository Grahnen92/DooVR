#version 400
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexNormal;

//out vec3 interpolatedColor;
//out vec3 interpolatedNormal;
//out vec3 pos;
//out vec3 lPos;

out vec3 Position;
out vec3 Normal;

uniform mat4 MV;
uniform mat4 OMV;
uniform mat4 P;

//uniform mat3 NormalMatrix;


void main () 
{
	
	mat3 NormalMatrix = inverse(transpose(mat3(MV)));
		
	Position =  vec3( MV * vec4(VertexPosition, 1.0));
	Normal = normalize( NormalMatrix * VertexNormal);
	//Normal = vec3( OMV * vec4(VertexNormal, 0.0));

	//pos = vec3(pos4) / pos4.w;
	//lPos = lightPos;

	gl_Position =  P * MV * vec4(VertexPosition, 1.0);

}