#version 400
layout( location = 0 ) out vec4 FragColor;

in vec3 Position;
in vec3 Normal;

uniform vec4 lightPos;
uniform vec4 lightPos2;
uniform vec4 lightPos3;
uniform vec4 lightPos4;

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

	float distance0 = length(vec3(lightPos) - Position);
	float distance1 = length(vec3(lightPos2) - Position);
	float distance2 = length(vec3(lightPos3) - Position);
	float distance3 = length(vec3(lightPos4) - Position);
	float attenuation0 = 1.0f / (ATT_CONST + ATT_LINEAR * distance0 + ATT_QUAD * (distance0 * distance0)); 
	float attenuation1 = 1.0f / (ATT_CONST + ATT_LINEAR * distance1 + ATT_QUAD * (distance1 * distance1)); 
	float attenuation2 = 1.0f / (ATT_CONST + ATT_LINEAR * distance2 + ATT_QUAD * (distance2 * distance2)); 
	float attenuation3 = 1.0f / (ATT_CONST + ATT_LINEAR * distance3 + ATT_QUAD * (distance3 * distance3)); 
		
	// 0th
	vec3 s = normalize( vec3(lightPos) - Position ); // lightDir
	vec3 r = reflect( -s, n );						 // reflectDir
	vec3 LI = LightIntensity * ( Ka + Kd * max( dot(s, n), 0.0 )) * 0.3; //+ Ks * pow( max( dot(r,v), 0.0 ), Shininess ) * 0.3;
	
	// 1st
	vec3 s1 = normalize( vec3(lightPos2) - Position ); // lightDir
	vec3 r1 = reflect( -s1, n );						 // reflectDir
	vec3 LI2 = LightIntensity * ( Ka + Kd * max( dot(s1, n), 0.0 ))  + Ks * pow( max( dot(r1,v), 0.0 ), Shininess ) * attenuation2 * strength;
	// 2nd
	vec3 s2 = normalize( vec3(lightPos3) - Position ); // lightDir
	vec3 r2 = reflect( -s2, n );						 // reflectDir
	vec3 LI3 = LightIntensity * ( Ka + Kd * max( dot(s2, n), 0.0 ))  + Ks * pow( max( dot(r2,v), 0.0 ), Shininess ) * attenuation2 * strength;
	// 3rd
	vec3 s3 = normalize( vec3(lightPos4) - Position ); // lightDir
	vec3 r3 = reflect( -s2, n );						 // reflectDir
	vec3 LI4 = LightIntensity * ( Ka + Kd * max( dot(s3, n), 0.0 )) + Ks * pow( max( dot(r3,v), 0.0 ), Shininess ) * attenuation3 * strength;
	
	
	
	
	vec3 resultLight = (LI + LI2 + LI3 + LI4) / 4.0f;
	FragColor = vec4(resultLight, 1.0);
	
}