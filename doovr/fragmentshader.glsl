#version 400
layout( location = 0 ) out vec4 FragColor;

in vec3 Position;
in vec3 Normal;
in vec2 UV;

uniform vec4 lightPos;
uniform sampler2D tex;

//uniform bool blinn;

void main () {

	vec3 LightIntensity = vec3(0.9f,0.9f,0.9f);

	vec3 Kd = vec3(0.7f, 0.7f, 0.7f);                // Diffuse reflectivity
	vec3 Ka = vec3(0.1f, 0.1f, 0.1f);                // Ambient reflectivity
	vec3 Ks = vec3( 0.9f, 0.9f, 0.9f);				 // Specular reflectivity

	// DXT from directX, so we have to invert the UV coordinates (coord.u, 1.0-coord.v) to fetch the correct texel.
	vec2 invUV = vec2(UV.x, 1.0-UV.y);

	vec3 texcolor = texture( tex, invUV ).rgb;
	
	
	// Ambient
    vec3 ambient = 0.05 * texcolor;

	//Diffuse part
	vec3 normal  = normalize( Normal );												//
	vec3 lightDir = normalize( vec3(lightPos) - Position );							// lightDir
	float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * texcolor;

	//specular part
	vec3 viewDir  = normalize(vec3(-Position));								       	// viewDir
	vec3 reflectDir  = reflect( -lightDir, normal  );								// reflectDir
	float Shininess = 4.0f;															// Specular shininess factor

	float spec = 0.0;
	if( true ) 
	{
		// Ambient
		ambient = 0.3 * texcolor;
		vec3 halfwayDir = normalize(lightDir + viewDir);  
        spec = pow(max(dot(normal, halfwayDir), 0.0), 16.0);
	}
	else
    {
		// Ambient
		ambient = 0.8 * texcolor;
        vec3 reflectDir = reflect(-lightDir, normal);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
    }

	vec3 specular = vec3(0.3) * spec;												// assuming bright white light color
    FragColor = vec4(ambient + diffuse + specular, 1.0f);

	//vec3 LI = LightIntensity * ( Ka + Kd * max( dot(lightDir, normal ), 0.0 )); // + Ks * pow( max( dot(r,viewDir ), 0.0 ), Shininess );
	// // DXT from directX, so we have to invert the UV coordinates (coord.u, 1.0-coord.v) to fetch the correct texel.
	//vec2 invUV = vec2(UV.x, 1.0-UV.y);
	//FragColor = texcolor * vec4(LI, 1.0);
	
}