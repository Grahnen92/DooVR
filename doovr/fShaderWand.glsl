#version 400
layout( location = 0 ) out vec4 FragColor;

in vec3 Position;
in vec3 Normal;

void main () {

	FragColor = vec4(0.2, 0.2, 0.2, 0.3); 

}