#version 400
layout( location = 0 ) out vec4 FragColor;

in vec3 Position;
in vec3 Normal;

const int nLightsources = 4;
const float ATT_CONST = 0.2f;
const float ATT_LINEAR = 0.4f;
const float ATT_QUAD = 0.8f;

uniform vec3 lightPos[nLightsources];

vec3 calculateLight(vec3 lightP, float lightIntensity) {


	vec3 color = vec3(0.6098f,0.5745f,0.6274f);
	
	//Diffuse part
	vec3 normal  = normalize( Normal );							
	vec3 lightDir = normalize(lightP - Position );				// lightDir
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = vec3(1.0f, 1.0f, 1.0f) * diff * lightIntensity;

	//specular part
	vec3 viewDir  = normalize(vec3(-Position));			    	// viewDir
	vec3 reflectDir  = reflect( -lightDir, normal  );			// reflectDir
	float Shininess = 4.0f;										// Specular shininess factor

	float spec = 0.0;
	// Ambient
	vec3 ambient = vec3(1.0f, 1.0f, 1.0f) * lightIntensity;
	vec3 halfwayDir = normalize(lightDir + viewDir);  
	spec = pow(max(dot(normal, halfwayDir), 0.0), 16.0);
	vec3 specular = vec3(1.0f, 1.0f, 1.0f) * spec * lightIntensity;			// assuming bright white light color
	return color*(ambient + diffuse + specular);
}


void main () {
	float LightIntensity = 0.0f;
	vec3 resultLight = calculateLight(lightPos[0], LightIntensity);
	LightIntensity = 0.15f;
	for (int i = 1; i < nLightsources; i++)
		resultLight += calculateLight(lightPos[i], LightIntensity);
	FragColor = vec4(resultLight, 1.0f);
	
}