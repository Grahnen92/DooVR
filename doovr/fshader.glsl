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
	vec3 Ks = vec3( 0.4f, 0.4f, 0.4f);				 // Specular reflectivity
	float Shininess = 4.0f;						 // Specular shininess factor
	vec3 norm = normalize( Normal );			
	vec3 vie = normalize(vec3(-Position));			 // viewDir	
		
	float strength = 0.5f;

	//float distance0 = length( vec3(lightPos) - Position);
	
	// 0th
	vec3 s = normalize( vec3(lightPos) - Position ); // lightDir
	//vec3 s = vec3(1.0f, 1.0f, 1.0f);
	vec3 r = reflect( -s, norm );						 // reflectDir
	vec3 LI = LightIntensity * (  Ka + Kd * max( dot(s, norm), 0.0 )) * 0.3; //+ Ks * pow( max( dot(r,v), 0.0 ), Shininess ) * 0.3;

	vec3 s2 = normalize( vec3(lightPos2) - Position ); // lightDir
	vec3 r2 = reflect( -s2, norm );						 // reflectDir
	vec3 LI2 = LightIntensity * (  Ka + Kd * max( dot(s2, norm), 0.0 )) * 0.3 + Ks * pow( max( dot(r2,vie), 0.0 ), Shininess ) * 0.3;

	vec3 s3 = normalize( vec3(lightPos3) - Position ); // lightDir
	vec3 r3 = reflect( -s3, norm );						 // reflectDir
	vec3 LI3 = LightIntensity * (  Ka + Kd * max( dot(s3, norm), 0.0 )) * 0.3 + Ks * pow( max( dot(r3,vie), 0.0 ), Shininess ) * 0.3;

	vec3 s4 = normalize( vec3(lightPos4) - Position ); // lightDir
	vec3 r4 = reflect( -s4, norm );						 // reflectDir
	vec3 LI4 = LightIntensity * (  Ka + Kd * max( dot(s4, norm), 0.0 )) * 0.3 + Ks * pow( max( dot(r4,vie), 0.0 ), Shininess ) * 0.3;
	
	vec3 resultLight = (LI + LI2 + LI3 +LI4)/4.0f;
	//vec3 resultLight = vec3(0.1f, 0.1f, 0.1f);
	FragColor = vec4(resultLight, 1.0);
	
}