#version 400
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexNormal;

//out vec3 Position;
//out vec3 Normal;
out vec3 resultLight;

uniform mat4 MV;
uniform mat4 P;
uniform vec4 lightPos;
uniform vec4 lightPos2;

void main () 
{
	vec3 Position =  vec3( MV * vec4(VertexPosition, 1.0));
	vec3 Normal = normalize(mat3(MV) * VertexNormal);

	vec3 LightIntensity = vec3(0.58039f,0.423529f, 0.282352f);

	vec3 Kd = vec3(0.8f, 0.8f, 0.8f);                // Diffuse reflectivity
	vec3 Ka = vec3(0.1f, 0.1f, 0.1f);                // Ambient reflectivity
	vec3 Ks = vec3( 0.7f, 0.7f, 0.7f);				 // Specular reflectivity
	float Shininess = 8.0f;						 // Specular shininess factor
	vec3 norm = normalize( Normal );			
	vec3 vie = normalize(vec3(-Position));			 // viewDir	
		
	float strength = 0.8f;

	//float distance0 = length( vec3(lightPos) - Position);
	
	// 0th
	vec3 s = normalize( vec3(lightPos) - Position ); // lightDir
	vec3 r = reflect( -s, norm );						 // reflectDir
	vec3 LI = LightIntensity * (  Ka + Kd * max( dot(s, norm), 0.0 )) + Ks * pow( max( dot(r,vie), 0.0 ), Shininess ) * strength;

	vec3 s2 = normalize( vec3(lightPos2) - Position ); // lightDir
	vec3 r2 = reflect( -s2, norm );						 // reflectDir
	vec3 LI2 = LightIntensity * (  Ka + Kd * max( dot(s2, norm), 0.0 ))  + Ks * pow( max( dot(r2,vie), 0.0 ), Shininess ) * strength;
	
	resultLight = (LI + LI2 )/2.0f;

	//! Convert position to clip coordinates and pass along to fragment shader
	gl_Position =  (P * MV) * vec4(VertexPosition, 1.0);

}