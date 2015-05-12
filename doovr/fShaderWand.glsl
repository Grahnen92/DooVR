#version 400
layout( location = 0 ) out vec4 FragColor;

in vec3 Position;
in vec3 Normal;

uniform vec4 lightPos;

void main () {

	gl_FragColor = vec4(0.2, 0.2, 0.2, 0.3); 

}