#version 400
layout( location = 0 ) out vec4 FragColor;

in vec3 Position;
in vec3 Normal;
in vec2 UV;

uniform vec4 lightPos;
uniform sampler2D tex;

void main () {
	float lightIntensity = 0.7f;

	// DXT from directX, so we have to invert the UV coordinates 
	//(coord.u, 1.0-coord.v) to fetch the correct texel.
	vec2 invUV = vec2(UV.x, 1.0-UV.y);
	vec3 texcolor = texture( tex, invUV ).rgb;
	
	//Diffuse part-----------
	vec3 normal  = normalize( Normal );							
	vec3 lightDir = normalize(vec3(lightPos) - Position );				// lightDir
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * texcolor * lightIntensity;

	//specular part-------------
	//vec3 viewDir  = normalize(vec3(-Position));			    	// viewDir
	//--onlyforphong--// vec3 reflectDir  = reflect( -lightDir, normal  );			// reflectDir
	//float Shininess = 4.0f;										// Specular shininess factor
	//vec3 halfwayDir = normalize(lightDir + viewDir);  
	//float spec = pow(max(dot(normal, halfwayDir), 0.0), 16.0);
	//vec3 specular = vec3(1.0f, 1.0f, 1.0f) * spec * lightIntensity;			// assuming bright white light color

	// Ambient-------------
	vec3 ambient = 0.3 * texcolor * lightIntensity;
	
	vec3 resultLight = ambient + diffuse; //+ specular;
	FragColor = vec4(resultLight, 1.0f);
	
}

