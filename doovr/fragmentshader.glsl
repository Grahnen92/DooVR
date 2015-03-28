#version 400

in vec3 Position;
in vec3 Normal;

//in vec3 interpolatedNormal;
//in vec3 interpolatedColor;
//in vec3 pos;
//in vec3 lPos;

uniform vec4 lightPos;
//uniform vec3 LightIntensity;
//uniform vec3 Kd = vec3(0.9f, 0.5f, 0.3f);                // Diffuse reflectivity
//uniform vec3 Ka = vec3(0.1f, 0.1f, 0.1f);                // Ambient reflectivity
//uniform vec3 Ks = vec3( 0.95f, 0.95f, 0.95f);            // Specular reflectivity
//uniform float Shininess = 100.0f;						 // Specular shininess factor

//out vec4 frag_colour;
layout( location = 0 ) out vec4 FragColor;

void main () {

    //// Ambient, diffuse and specular constants. nS is a notation on shininess (higher = more shiny)
	//float kA = 0.3;
	//float kS = 0.4;
	//float kD = 0.5;
	//float nS = 4;
	//float shine = 50;
	//float dLight;
	//float sLight;
	//float sAngle;

	//vec3 normal = normalize(interpolatedNormal);
	//vec3 lightDir = normalize(lPos - pos);
	//vec3 viewDir = normalize(-pos);

	//dLight = max(dot(lightDir, interpolatedNormal), 0.0f);
	//dLight = clamp(dLight, 0.0f, 1.0f);
	//dLight = max(dLight, 0);
	//dLight = min(dLight, 1);

	//vec3 halfDir = normalize(lightDir + viewDir);
    //sAngle = max(dot(halfDir, normal), 0.0);
    //sLight = pow(sAngle, 16.0);

	//vec3 reflectDir = reflect(-lightDir, normal);
    //sAngle = max(dot(reflectDir, viewDir), 0.0);
    //sLight = pow(sAngle, 8.0);
	
	//vec3 Color = interpolatedColor*dLight;//*sLight + vec3(0.05f);


	vec3 LightIntensity = vec3(0.9f,0.9f,0.9f);

	vec3 Kd = vec3(0.7f, 0.7f, 0.7f);                // Diffuse reflectivity
	vec3 Ka = vec3(0.1f, 0.1f, 0.1f);                // Ambient reflectivity
	vec3 Ks = vec3( 0.9f, 0.9f, 0.9f);            // Specular reflectivity
	float Shininess = 180.0f;						 // Specular shininess factor

	vec3 n = normalize( Normal );					//
	vec3 s = normalize( vec3(lightPos) - Position );//lightDir
	vec3 v = normalize(vec3(-Position));			//viewDir
	vec3 r = reflect( -s, n );						//reflectDir
	vec3 LI = LightIntensity * ( Ka + Kd * max( dot(s, n), 0.0 ) + Ks * pow( max( dot(r,v), 0.0 ), Shininess ) );

	//frag_colour = vec4(LI, 1.0);
	FragColor = vec4(LI, 1.0);

}