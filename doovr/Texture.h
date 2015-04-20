#include "Utilities.h"


class Texture {
public:
	Texture();
	~Texture();

	Texture(char* filepath);

	GLuint loadDDS(const char * imagepath);

	GLuint getTextureID() { return textureID; }

private: 
	GLuint textureID;

};