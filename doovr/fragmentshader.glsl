#version 400
layout( location = 0 ) out vec4 FragColor;

in vec3 Position;
in vec3 Normal;
in vec2 UV;

uniform vec4 lightPos;
uniform sampler2D tex;

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

	vec3 LI = LightIntensity * ( Ka + Kd * max( dot(s, n), 0.0 )); // + Ks * pow( max( dot(r,v), 0.0 ), Shininess );
	

	// DXT from directX, so we have to invert the UV coordinates (coord.u, 1.0-coord.v) to fetch the correct texel.
	vec2 invUV = vec2(UV.x, 1.0-UV.y);

	vec4 texcolor = texture( tex, invUV );
	FragColor = texcolor * vec4(LI, 1.0);
	
}