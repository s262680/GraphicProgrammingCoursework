#pragma once
#include <string>
#include <GL\glew.h>
#include "ModelMesh.h"
#include "MyCamera.h"

class MyShader
{
public:

	//create constructor and destructor
	MyShader(const std::string& filename);
	~MyShader();

	//public functions
	void Bind(); 
	void Update(const ModelMesh& modelMesh, const MyCamera& camera);
	std::string MyShader::ShaderLoader(const std::string& fileName);
	void MyShader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint MyShader::GenerateShader(const std::string& text, unsigned int type);




protected:
private:

	//set the numbers of shaders
	static const unsigned int NUM_SHADERS = 2;

	//a pack num start from 0 and increase by 1 for each content
	enum
	{
		TRANSFORM_U,
		NUM_UNIFORMS
	};

	//a variable that use for store the shader program as reference number
	GLuint program; 

	//array of shaders and uniforms
	GLuint shaders[NUM_SHADERS]; 
	GLuint uniforms[NUM_UNIFORMS]; 
};
