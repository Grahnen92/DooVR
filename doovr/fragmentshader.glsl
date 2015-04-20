#version 400
layout( location = 0 ) out vec4 FragColor;

in vec3 Position;
in vec3 Normal;
// Interpolated values from the vertex shaders
in vec2 UV;

uniform vec4 lightPos;
uniform sampler2D tex;

//out vec4 frag_colour;
// Ouput data
out vec3 color;

void main () {

	vec3 LightIntensity = vec3(0.9f,0.9f,0.9f);

	vec3 Kd = vec3(0.7f, 0.7f, 0.7f);                // Diffuse reflectivity
	vec3 Ka = vec3(0.1f, 0.1f, 0.1f);                // Ambient reflectivity
	vec3 Ks = vec3( 0.9f, 0.9f, 0.9f);				 // Specular reflectivity
	float Shininess = 4.0f;						 // Specular shininess factor

	vec3 n = normalize( Normal );					 //
	vec3 s = normalize( vec3(lightPos) - Position ); // lightDir
	vec3 v = normalize(vec3(-Position));			 // viewDir
	vec3 r = reflect( -s, n );						 // reflectDir

	vec3 LI = LightIntensity * ( Ka + Kd * max( dot(s, n), 0.0 )) + Ks * pow( max( dot(r,v), 0.0 ), Shininess );

	color = texture( tex, UV ).rgb;

	//frag_colour = vec4(LI, 1.0);
	FragColor = vec4(LI, 1.0) + vec4(color, 1.0);

	

}