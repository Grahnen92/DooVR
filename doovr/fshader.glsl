#version 400
layout( location = 0 ) out vec4 FragColor;

in vec3 Position;
in vec3 Normal;

uniform vec3 LP1;

const float ATT_CONST = 0.2f;
const float ATT_LINEAR = 0.4f;
const float ATT_QUAD = 0.8f;

void main () {
	vec3 LightIntensity = vec3(0.6098f,0.5745f,0.6274f);

	vec3 Kd = vec3(0.6f, 0.6f, 0.6f);                // Diffuse reflectivity
	vec3 Ka = vec3(0.1f, 0.1f, 0.1f);                // Ambient reflectivity
	vec3 Ks = vec3( 0.9f, 0.9f, 0.9f);				 // Specular reflectivity
	float Shininess = 4.0f;						 // Specular shininess factor
	vec3 n = normalize( Normal );			
	vec3 v = normalize(vec3(-Position));			 // viewDir	
		
	float strength = 0.5f;

	float distance0 = length(vec3(LP1) - Position);
	
	// 0th
	vec3 s = normalize( vec3(LP1) - Position ); // lightDir
	vec3 r = reflect( -s, n );						 // reflectDir
	vec3 LI = LightIntensity * ( Ka + Kd * max( dot(s, n), 0.0 )) * 0.3; //+ Ks * pow( max( dot(r,v), 0.0 ), Shininess ) * 0.3;
	
	vec3 resultLight = LI;
	FragColor = vec4(resultLight, 1.0);
	
}