#version 400
layout( location = 0 ) out vec4 FragColor;

//in vec3 Position;
//in vec3 Normal;
in vec3 resultLight;

void main () {

	FragColor = vec4(resultLight, 1.0);
	
}