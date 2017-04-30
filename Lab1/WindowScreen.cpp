#include <iostream>
#include "WindowScreen.h"


//default window values
WindowScreen::WindowScreen()
{
	window = nullptr;
	width = 1024.0f;
	height = 768.0f;
}

//delete context, window and quit the application at the end
WindowScreen::~WindowScreen()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//swap buffer
void WindowScreen::swapBuffer()
{
	SDL_GL_SwapWindow(window);
}


void WindowScreen::initial()
{

	//initial everything
	SDL_Init(SDL_INIT_EVERYTHING);

	//minimize number of bit that used for colour
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

	//set up depth buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

	//set up double buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//creating window with specificed position and size
	window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)width, (int)height, SDL_WINDOW_OPENGL);

	//return error message if no window found
	if (window == nullptr)
	{
		errorMsg("Failed to create window");
	}

	//create gl context
	glContext = SDL_GL_CreateContext(window);

	//return error message if no context found
	if (glContext == nullptr)
	{
		errorMsg("Failed to initialise SDL_GL context");
	}

	GLenum error = glewInit();

	//return error message if glew is unable to initialise
	if (error != GLEW_OK)
	{
		errorMsg("GLEW failed to initialise");
	}

	//enable depth buffer
	glEnable(GL_DEPTH_TEST);

	//avoid drawing faces that cannot be seen by camera
	glEnable(GL_CULL_FACE);

	//passing clear values to the color buffer
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}


void WindowScreen::clearScreenDisplay(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void WindowScreen::errorMsg(string msg)
{
	cout << msg << endl;
	cout << "press any key to quit";

	int in;
	cin >> in;
	SDL_Quit();
}

