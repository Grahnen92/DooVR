#version 400
layout( location = 0 ) out vec4 FragColor;

in vec3 Position;
in vec3 Normal;
in vec2 UV;


uniform vec4 lightPos;
uniform sampler2D tex;

vec3 calculateLight(vec3 lightP, float lightIntensity) {
	// DXT from directX, so we have to invert the UV coordinates 
	//(coord.u, 1.0-coord.v) to fetch the correct texel.
	vec2 invUV = vec2(UV.x, 1.0-UV.y);
	vec3 texcolor = texture( tex, invUV ).rgb;
	
	
	//Diffuse part
	vec3 normal  = normalize( Normal );							
	vec3 lightDir = normalize(lightP - Position );				// lightDir
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * texcolor * lightIntensity;

	//specular part
	vec3 viewDir  = normalize(vec3(-Position));			    	// viewDir
	vec3 reflectDir  = reflect( -lightDir, normal  );			// reflectDir
	float Shininess = 4.0f;										// Specular shininess factor

	float spec = 0.0;
	// Ambient
	vec3 ambient = 0.3 * texcolor * lightIntensity;
	vec3 halfwayDir = normalize(lightDir + viewDir);  
	spec = pow(max(dot(normal, halfwayDir), 0.0), 16.0);
	vec3 specular = vec3(1.0f, 1.0f, 1.0f) * spec * lightIntensity;			// assuming bright white light color
	
	return ambient + diffuse;// + specular;
}


void main () {
	float LightIntensity = 0.7f;
	vec3 resultLight = calculateLight(vec3(lightPos), LightIntensity);
	FragColor = vec4(resultLight, 1.0f);
	
}

