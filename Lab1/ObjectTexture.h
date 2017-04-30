#pragma once
#include <string>
#include <GL\glew.h>
using namespace std;
class ObjectTexture
{
public:

	//create constructor and destructor
	ObjectTexture();
	~ObjectTexture();

	//bind texture up to a specified number which will be the unit variable
	void Bind(unsigned int unit);

	//load texture from a specified file path
	void LoadTexture(const string& fileName);

	

protected:
private:

	GLuint texHolder;
};

