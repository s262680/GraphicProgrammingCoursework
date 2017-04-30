#pragma once
#include<glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"
#include <glm/gtx/transform.hpp>
using namespace std;



class ModelMesh
{
public:

	//create constructor and destructor
	ModelMesh();
	~ModelMesh();

	//public functions
	void ModelRender();
	void loadGameModel(const string& filename);
	void InitialGameModel(const IndexedModel& model);

	//calculation of model matrix
	glm::mat4 ModelMatrix() const
	{
		glm::mat4 positionMatrix = glm::translate(position);
		glm::mat4 scaleMatrix = glm::scale(scale);
		glm::mat4 rotationX = glm::rotate(rotation.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotationY = glm::rotate(rotation.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotationZ = glm::rotate(rotation.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotationMatrix = rotationX * rotationY * rotationZ;

		return positionMatrix * rotationMatrix * scaleMatrix;
	}

	//setter for model position, rotation and scale
	void SetPosition(glm::vec3& position) { this->position = position; }
	void SetRotation(glm::vec3& rotation) { this->rotation = rotation; }
	void SetScale(glm::vec3& scale) { this->scale = scale; }

private:

	//a pack num start from 0 and increase by 1 for each content
	enum 
	{
		POSITION_VERTEXBUFFER,
		TEXTURECOORDS_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	//create vertex array object and buffer
	GLuint VAO;
	GLuint VAB[NUM_BUFFERS];
	//number of vertex array object
	unsigned int drawCounter;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};