#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <string>
#include <iostream>

using namespace std;

class WindowScreen
{
public:

	//create constructor and destructor
	WindowScreen();
	~WindowScreen();

	//public function
	void initial();
	void swapBuffer();
	void clearScreenDisplay(float r, float g, float b, float a);

	//getter of screen width and heigh
	float getScreenWidth(){return width;}
	float getScreenHeight(){return height;}
private:

	//output error message
	void errorMsg(string msg);

	//width and height variable for the display
	float width = 1024.0f;;
	float height = 768.0f;;

	//hold window pointer 
	SDL_Window* window;

	//hold context
	SDL_GLContext glContext;
};
