#pragma once

#include<GL/glew.h>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__,__LINE__))
#define WIN_WIDTH 1960
#define WIN_HEIGHT 1080

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);