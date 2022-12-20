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
#include "AllocationScene.h"
#include "AssignmentScene.h"
#include "GameMainScene.h"
#include "TextRender.h"

//#include "GameLogic/Game.hpp"
//#include "GameLogic/Game_Object.hpp"

#include "GameLogic/Teammate.h"
#include "GameLogic/Mission.h"

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
	window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "International Game Jam", NULL, NULL);
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
		scene::GameMainScene* MainScene = new scene::GameMainScene;
		scene::AssignmentScene* AssignmentScene = new scene::AssignmentScene;
		scene::AllocationScene* AllocScene = new scene::AllocationScene;

		std::vector<scene::Base*> ScenesRegister;
		ScenesRegister.push_back(MenuScene);
		ScenesRegister.push_back(MainScene);
		ScenesRegister.push_back(AssignmentScene);
		ScenesRegister.push_back(AllocScene);

		//currentScene = MenuScene;
		currentScene = MenuScene;

		//GameLogic Init
		Member CH(1), MG(2), CX(3);
		Mission m1(1, "Document"), m2(2, "Draw"), m3(3, "Program");
		std::vector<Member> member;
		member.push_back(CH);
		member.push_back(MG);
		member.push_back(CX);
		std::vector<Mission> mission;
		mission.push_back(m1);
		mission.push_back(m2);
		mission.push_back(m3);


		int state = 0;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			state++;
			/* Render here */
			
			currentScene->SceneChangeController(window,currentScene,ScenesRegister,member,mission);
			currentScene->OnRender(textrender,member,mission);

			if (state%10 == 0)
			{
				if (mission[0].GetisDoing() && member[0].GetEfficiency() > 40)
				{
					member[0].ChangeMood(-5);
					mission[0].ChangeProgress(5);
					std::cout <<"CH: Mood" << member[0].GetEfficiency() << " Progress " << mission[0].GetProgress() << std::endl;
				}

				if (mission[1].GetisDoing() && member[1].GetEfficiency() > 40)
				{
					member[1].ChangeMood(-5);
					mission[1].ChangeProgress(5);
					std::cout << "MG: Mood" << member[1].GetEfficiency() << " Progress " << mission[1].GetProgress() << std::endl;
				}

				if (mission[2].GetisDoing()&&member[2].GetEfficiency()>40)
				{
					member[2].ChangeMood(-5);
					mission[2].ChangeProgress(5);
					std::cout << "CX: Mood" << member[2].GetEfficiency() << " Progress " << mission[2].GetProgress() << std::endl;
				}
			}

			if (mission[0].GetProgress() >= 100 && mission[1].GetProgress() >= 100 && mission[2].GetProgress() >= 100)
			{
				textrender.RenderText("FINISH!", 500.0f, 500.0f, 3.0f, glm::vec3(1, 1, 0));
			}

			

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	glfwTerminate();
	return 0;
}
