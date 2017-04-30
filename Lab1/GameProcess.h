#pragma once

#include <SDL\SDL.h>
#include <GL/glew.h>

#include "WindowScreen.h"
#include "MyShader.h"
#include "ModelMesh.h"
#include "ObjectTexture.h"
#include "MyCamera.h"

//setup enum for game state play and exit
//where play =0 and exit =1;
enum class GameState{PLAY, EXIT};

class GameProcess
{
public:


	//create constructor and destructor
	GameProcess();
	~GameProcess();
	
	//a public process function that call by the main class
	void process();


	void MouseRotation(float x, float y);

private:

	//private functions for this class
	void initial();
	void input();
	void loop();
	void render();


	//private variables for this class
	WindowScreen gameScreen;
	GameState gameState;
	ModelMesh modelMesh1;
	ModelMesh modelMesh2;
	ModelMesh modelMesh3;
	MyCamera myCamera;
	ObjectTexture texture1;
	ObjectTexture texture2;
	ObjectTexture texture3;
	ModelMesh modelMesh;

	//ModelMesh* m_TestGO;

	vector<ModelMesh*> GOList;

	float ObjMove;
	float ObjRotate;
	bool shaderTrigger;
	string shaderPath;
};