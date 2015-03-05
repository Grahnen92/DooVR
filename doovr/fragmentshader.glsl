#version 400

in vec3 interpolatedNormal;
in vec3 interpolatedColor;
in vec3 pos;

out vec4 frag_colour;

const vec3 lightPos = vec3(2.0f, 2.0f, 2.0f);

void main () {

    // Ambient, diffuse and specular constants. nS is a notation on shininess (higher = more shiny)
	float kA = 0.3;
	float kS = 0.4;
	float kD = 0.5;
	float nS = 4;
	float shine = 50;
	float dLight;
	float sLight;
	float sAngle;

	vec3 normal = normalize(interpolatedNormal);
	vec3 lightDir = normalize(lightPos - pos);

	vec3 viewDir = normalize(-pos);

	dLight = dot(lightDir, normal);

	dLight = max(dLight, 0);
	dLight = min(dLight, 1);

	vec3 halfDir = normalize(lightDir + viewDir);
    sAngle = max(dot(halfDir, normal), 0.0);
    sLight = pow(sAngle, 16.0);

	//vec3 reflectDir = reflect(-lightDir, normal);
    //sAngle = max(dot(reflectDir, viewDir), 0.0);
    //sLight = pow(sAngle, 8.0);
	
	vec3 Color = 0.5f*interpolatedColor*dLight + interpolatedColor*sLight;

	frag_colour = vec4(Color, 1.0);
}