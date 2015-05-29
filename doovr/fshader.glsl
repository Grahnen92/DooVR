#version 400
layout( location = 0 ) out vec4 FragColor;

in vec3 Position;
in vec3 Normal;

uniform vec4 lightPos;
uniform vec4 lightPos2;
//uniform vec4 lightPos3;
//uniform vec4 lightPos4;

const float ATT_CONST = 0.2f;
const float ATT_LINEAR = 0.4f;
const float ATT_QUAD = 0.8f;

void main () {
	//vec3 LightIntensity = vec3(0.8196f, 0.8039f, 0.7882f);
	//vec3 LightIntensity = vec3(0.851,0.816f,0.764f);
	//vec3 LightIntensity = vec3(0.58039f,0.454901f,0.452353f);
	vec3 LightIntensity = vec3(0.58039f,0.423529f, 0.282352f);
	//vec3 LightIntensity = vec3(0.6098f,0.5745f,0.6274f);

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
	//vec3 s = vec3(1.0f, 1.0f, 1.0f);
	vec3 r = reflect( -s, norm );						 // reflectDir
	vec3 LI = LightIntensity * (  Ka + Kd * max( dot(s, norm), 0.0 )) + Ks * pow( max( dot(r,vie), 0.0 ), Shininess ) * strength;

	vec3 s2 = normalize( vec3(lightPos2) - Position ); // lightDir
	vec3 r2 = reflect( -s2, norm );						 // reflectDir
	vec3 LI2 = LightIntensity * (  Ka + Kd * max( dot(s2, norm), 0.0 ))  + Ks * pow( max( dot(r2,vie), 0.0 ), Shininess ) * strength;

	//vec3 s3 = normalize( vec3(lightPos3) - Position ); // lightDir
	//vec3 r3 = reflect( -s3, norm );						 // reflectDir
	//vec3 LI3 = LightIntensity * (  Ka + Kd * max( dot(s3, norm), 0.0 )) + Ks * pow( max( dot(r3,vie), 0.0 ), Shininess ) * strength;

	//vec3 s4 = normalize( vec3(lightPos4) - Position ); // lightDir
	//vec3 r4 = reflect( -s4, norm );						 // reflectDir
	//vec3 LI4 = LightIntensity * (  Ka + Kd * max( dot(s4, norm), 0.0 ))  + Ks * pow( max( dot(r4,vie), 0.0 ), Shininess ) * strength;
	
	vec3 resultLight = (LI + LI2 )/2.0f;
	//vec3 resultLight = vec3(0.1f, 0.1f, 0.1f);
	FragColor = vec4(resultLight, 1.0);
	
}