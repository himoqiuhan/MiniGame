#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include <map>

#include "Renderer.hpp"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/detail/glm.cpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Base.h"
#include "MainMenu.h"
#include "Loading.h"
#include "AllocationScene.h"
#include "AssignmentScene.h"
#include "AttribScene.h"
#include "GameMainScene.h"
#include "TextRender.h"

// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	//Exchange our OpenGL version to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(5);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;

	glfwSwapInterval(10);

	// Define the viewport dimensions
	glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

	// Set OpenGL options
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Text textrender;

	{
		
		scene::Base* currentScene = nullptr;
		scene::MainMenu* MenuScene = new scene::MainMenu;
		scene::Loading* LoadingScene = new scene::Loading;
		scene::GameMainScene* MainScene = new scene::GameMainScene;
		scene::AttribScene* AttribScene = new scene::AttribScene;
		scene::AssignmentScene* AssignmentScene = new scene::AssignmentScene;
		scene::AllocationScene* AllocScene = new scene::AllocationScene;

		std::vector<scene::Base*> ScenesRegister;
		ScenesRegister.push_back(MenuScene);
		ScenesRegister.push_back(LoadingScene);
		ScenesRegister.push_back(MainScene);
		ScenesRegister.push_back(AttribScene);
		ScenesRegister.push_back(AssignmentScene);
		ScenesRegister.push_back(AllocScene);

		currentScene = MenuScene;


		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			
			/* Render here */
			
			currentScene->OnRender(textrender);
			currentScene->SceneChangeController(window,currentScene,ScenesRegister);






			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	glfwTerminate();
	return 0;
}
