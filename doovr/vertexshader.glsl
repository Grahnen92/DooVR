#version 400
layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;

uniform mat4 MV;
uniform mat4 P;

uniform vec3 lightPosition;
uniform vec3 cameraPosition;
uniform vec3 objectPosition;
uniform vec3 objectColor;

out vec3 interpolatedColor;
out vec3 interpolatedNormal;


void main () 
{
    // Ambient, diffuse and specular constants. nS is a notation on shininess (higher = more shiny)
	float kA = 0.3;
	float kS = 0.4;
	float kD = 0.5;
	float nS = 4;

	gl_Position = P * MV * vec4 (Position, 1.0);
	interpolatedNormal = mat3(MV) * Normal;
	vec3 lightDirection =  lightPosition - vec3(gl_Position) ;
	lightDirection.z = -lightDirection.z;
	

	vec3 reflection = reflect(normalize(-lightDirection), normalize(interpolatedNormal));
	vec3 cameraDirection = cameraPosition - vec3(gl_Position);
	
	float sLight;
	float dLight = dot(normalize(interpolatedNormal), normalize(lightDirection));
	if (dot(interpolatedNormal, lightDirection) < 0.0) {
		sLight = 0.0;
	}
	else {
		sLight = dot(normalize(reflection), normalize(cameraDirection));
	sLight = max(0, sLight);
	}
	
	dLight = max(0, dLight);

    // totalLightinPixel = (Ambient + Diffuse + Specular light)*objectColor
	interpolatedColor = kA *objectColor + kD * dLight * vec3(1.0, 1.0, 1.0) +  kS * pow(sLight, nS) * vec3(1.0, 1.0, 1.0);
    
}