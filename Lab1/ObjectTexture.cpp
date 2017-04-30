#include "ObjectTexture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>
using namespace std;

//default constractor, set up and not using memory until its actually being use
ObjectTexture::ObjectTexture()
{
}

void ObjectTexture::LoadTexture(const string&fileName)
{
	//variables for width, height and number of component
	int width, height, numComponents; 

	//load the image from the specified file and store it into the variable
	unsigned char* imgData = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

	//return msg if no data found
	if (imgData == NULL)
	{
		cerr << "unable to find any texture" << fileName << endl;
	}

	//generate texture based on the number and address of textures
	glGenTextures(1, &texHolder);

	//bind texture with specify type
	glBindTexture(GL_TEXTURE_2D, texHolder);

	//set up texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

	//specify a 2d texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData); 
	
	//free the loaded image
	stbi_image_free(imgData);
}

ObjectTexture::~ObjectTexture()
{
	//delete texture
	glDeleteTextures(1, &texHolder);
}

void ObjectTexture::Bind(unsigned int unit)
{
	//check if the textures are within range, if not terminate the program
	assert(unit >= 0 && unit <= 31); 

	//select active texture unit
	glActiveTexture(GL_TEXTURE0 + unit); 

	//bind texture with specify type
	glBindTexture(GL_TEXTURE_2D, texHolder);
}
