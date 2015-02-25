#version 400

in vec3 interpolatedNormal;
in vec3 interpolatedColor;

out vec4 frag_colour;
void main () 

{
	frag_colour = vec4(interpolatedColor, 1.0);
}