#version 400

in vec3 interpolatedNormal;
in vec3 interpolatedColor;

out vec4 frag_colour;


void main () {

    // Ambient, diffuse and specular constants. nS is a notation on shininess (higher = more shiny)
	float kA = 0.3;
	float kS = 0.4;
	float kD = 0.5;
	float nS = 4;
	float shine = 50;
	float dLight;

	vec3 lightDirr = vec3(1.3f, 0.3f, 1.0f);
	vec3 camPos = vec3(1.0f, 0.5f, -1.0f);

	vec3 viewDirr = normalize(-camPos);

	dLight = dot(normalize(lightDirr), normalize(interpolatedNormal));

	dLight = max(dLight, 0);
	dLight = min(dLight, 1);

	vec3 halfAngle = normalize(lightDirr + viewDirr);
	float blinn = dot(normalize(interpolatedNormal), halfAngle);

	blinn = max(blinn, 0);

	blinn = dLight != 0.0 ? blinn : 0.0;
	blinn = pow(blinn, shine);

	
	
	vec3 Color = 0.5f*interpolatedColor*dLight + interpolatedColor*blinn;

	frag_colour = vec4(Color, 1.0);
}