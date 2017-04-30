#include "GameProcess.h"
#include "MyCamera.h"
#include <iostream>
#include <string>
using namespace std;


//store the resource path to a constant variable 
const string resPath = "C:\\Users\\csong200\\Desktop\\Coursework\\res\\";

//constructor
GameProcess::GameProcess()
{
	//set game state to "play"
	gameState = GameState::PLAY;

	//set up window screen
	WindowScreen* gameScreen = new WindowScreen();
	
	//give variable default values
	ObjMove = 0.0f;
	ObjRotate = 0.0f;

	//get default constructor
	ModelMesh* modelMesh();
	ObjectTexture* texture();

	shaderTrigger = false;
	shaderPath = shaderPath = resPath + "blur";;
}
GameProcess::~GameProcess()
{

}


//function that call by the main class at the very beginning
void GameProcess::process()
{
	//call initial and loop function
	initial();
	loop();
}


//function that initial the window, camera, models and textures 
void GameProcess::initial()
{

	//initial window screen
	gameScreen.initial();

	//initial camera by passing position, field of view, screen size, near and far clip
	myCamera.initCamera(glm::vec3(0, 0, -5), 70.0f, (float)gameScreen.getScreenWidth() / gameScreen.getScreenHeight(), 0.01f, 1000.0f);

	//load models from  specific paths
	modelMesh1.loadGameModel(resPath + "Brazuca.obj");
	modelMesh2.loadGameModel(resPath + "tree.obj");
	modelMesh3.loadGameModel(resPath + "casa.obj");

	//load textures from  specific paths
	texture1.LoadTexture(resPath + "brazuca.jpg");
	texture2.LoadTexture(resPath + "tree.jpg");
	texture3.LoadTexture(resPath + "bricks_diff.jpg");

}

//function that will constantly looping while the game state is not equal to "exit"
void GameProcess::loop()
{
	while (gameState != GameState::EXIT)
	{
		//input and draw function while looping
		input();
		render();
	}
}

//function that takes several types of input and result
//moving or rotating camera or objects
void GameProcess::input()
{
	SDL_Event event;

	//while there is events in the queue
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{		
			//pass the mouse motion value to the mouse rotation function
		case SDL_MOUSEMOTION:
			MouseRotation(event.motion.xrel, event.motion.yrel);
			break;
			
		//close game when event type equal to quit
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;

		case SDL_KEYDOWN:
			//create a keytype variable to represent the keycode
			SDL_Keycode keyType = event.key.keysym.sym;

			//perform different action depending on the key type
			switch (keyType)
			{
			//camera movement
			case SDLK_w:
				myCamera.CamForwardMovement(0.1f);
				break;
			case SDLK_s:
				myCamera.CamBackwardMovement(0.1f);
				break;
			case SDLK_d:
				myCamera.CamRightMovement(0.1f);
				break;
			case SDLK_a:
				myCamera.CamLeftMovement(0.1f);
				break;

				
			//camera rotation by key press
			case SDLK_LEFT:
				myCamera.HorizonRotation(0.1f);
				break;
			case SDLK_RIGHT:
				myCamera.HorizonRotation(-0.1f);
				break;
				
			case SDLK_UP:
				myCamera.VerticalRotation(-0.1f);
				break;
			case SDLK_DOWN:
				myCamera.VerticalRotation(0.1f);
				break;

			
			//objects rotation
			case SDLK_h:
				ObjRotate += 0.1f;
				break;
			case SDLK_k:
				ObjRotate -= 0.1f;
				break;
			//objects movement
			case SDLK_u:
				ObjMove += 0.1f;
				break;
			case SDLK_j:
				ObjMove -= 0.1f;
				break;

			case SDLK_r:
				if (!shaderTrigger)
				{
					shaderTrigger = true;
					shaderPath = resPath + "shader";
				}
				else if (shaderTrigger)
				{
					shaderTrigger = false;
					shaderPath = resPath + "blur";
				}
				break;
			
		}
			break;
		}

	
	}
}


//function that allows camera rotation by using mouse motion
void GameProcess::MouseRotation(float x, float y)
{
	if (!(x*0.002f > 0.1f) && !(y*0.002f > 0.1f))
	{
		myCamera.HorizonRotation(-x*0.002f);
	
		myCamera.VerticalRotation(y*0.002f);
	}
}


//function that render the scene
void GameProcess::render()
{
	//call clearScreenDisplay function and pass in colour value
	gameScreen.clearScreenDisplay(0.0f, 0.0f, 0.0f, 1.0f);

	
	//create shader program from a specific path

	MyShader shader(shaderPath);
	

	//position, rotation and scale for first game object on the scene
	//values will change based on the input by modify the ObjMove and ObjRotate value
	modelMesh.SetPosition(glm::vec3(ObjMove+2, -2.0, 0.0));
	modelMesh.SetRotation(glm::vec3(0.0, ObjRotate, 0.0));
	modelMesh.SetScale(glm::vec3(0.7, 0.7, 0.7));
	//bind the shader
	shader.Bind();
	//call update function from shader class
	shader.Update(modelMesh, myCamera);
	//bind the first texture
	texture1.Bind(0);
	//call draw function from modelMesh class
	modelMesh1.ModelRender();


	//same as above
	modelMesh.SetPosition(glm::vec3(ObjMove, -1.5, 0.0));
	modelMesh.SetRotation(glm::vec3(0.0, ObjRotate, 0.0));
	modelMesh.SetScale(glm::vec3(0.2, 0.2, 0.2));
	shader.Update(modelMesh, myCamera);
	texture2.Bind(0);
	modelMesh2.ModelRender();


	modelMesh.SetPosition(glm::vec3(ObjMove - 2, -1.8, 0.0));
	modelMesh.SetRotation(glm::vec3(0.0, ObjRotate, 0.0));
	modelMesh.SetScale(glm::vec3(0.5, 0.5, 0.5));
	shader.Update(modelMesh, myCamera);
	texture3.Bind(0);
	modelMesh3.ModelRender();

	//enable colour array for used during rendering
	glEnableClientState(GL_COLOR_ARRAY);

	//end of vertex data
	glEnd();

	//call swapBuffer function from gameScreen class
	gameScreen.swapBuffer();
}


