#include "MyShader.h"
#include <iostream>
#include <fstream>
using namespace std;

//const string resPath = "C:\\Users\\csong200\\Desktop\\Coursework\\res\\";

MyShader::MyShader(const std::string& filename)
{
	//the glCreateProgram function will create a shader program and store it
	//in to the variable as reference number
	program = glCreateProgram();

	//a vertex shader and fragment shader are created from specified file and store into an array
	shaders[0] = GenerateShader(ShaderLoader(filename + ".vert"), GL_VERTEX_SHADER);
	shaders[1] = GenerateShader(ShaderLoader(filename + ".frag"), GL_FRAGMENT_SHADER);


	//loop through the shaders array and attach each shader to the shader program
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(program, shaders[i]); 
	}

	//associate a generic vertex attribute index with a attribute variable
	glBindAttribLocation(program, 0, "position");  
	glBindAttribLocation(program, 1, "texCoord");

	//link a specified program object
	glLinkProgram(program); 

	//check to see if there is any error on linking
	CheckShaderError(program, GL_LINK_STATUS, true, "Fail to link shader program"); 

	//check to see if the program can execute
	glValidateProgram(program);

	//check to see if there is any error on validation
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Shader program is not valid");

	//store the location of the uniform in to a variable
	uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform"); 
}


//detach and delect all the shaders and program
MyShader::~MyShader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(program, shaders[i]); 
		glDeleteShader(shaders[i]); 
	}
	glDeleteProgram(program); 
}

void MyShader::Bind()
{
	//install a specified program object
	glUseProgram(program); 
}

//update the model and camera matrices and pass it to the shader
void MyShader::Update(const ModelMesh& modelMesh, const MyCamera& camera)
{
	glm::mat4 mvp = camera.GetCamViewProjection() * modelMesh.ModelMatrix();
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GLU_FALSE, &mvp[0][0]);
}


GLuint MyShader::GenerateShader(const std::string& text, unsigned int type)
{
	//create the shader with a specify type such as vertex shader or fragment shader
	GLuint shader = glCreateShader(type); 

	//return error if no shader found
	if (shader == 0) 
		std::cerr << "Unable to locat shader " << type << std::endl;

	//convert the text string to character string
	const GLchar* stringSource[1]; 
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	//set source code in shader to the source code in stringSource array
	glShaderSource(shader, 1, stringSource, lengths);

	//compile the shader object
	glCompileShader(shader); 

	//check to see if there is any compile error
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "shader compile error!"); 

	return shader;
}


//function that allows load shader taking the shader file path as arguement 
std::string MyShader::ShaderLoader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "The following shader cannot be load: " << fileName << std::endl;
	}

	return output;
}


//function that allows to check error for shader based on specify status type 
void MyShader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

