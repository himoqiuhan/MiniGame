#include "GameMainScene.h"

namespace scene
{

	GameMainScene::GameMainScene()
		:m_TranslationA{ -1,0,0 },m_TranslationB{1,0,0},
		m_Proj(glm::ortho(-4.0f, 4.0f, -2.25f, 2.25f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{
		float positions[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, //0
			 0.5f, -0.5f, 1.0f, 0.0f, //1
			 0.5f,  0.5f, 1.0f, 1.0f, //2
			-0.5f,  0.5f, 0.0f, 1.0f, //3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();

		m_Texture = std::make_unique<Texture>("res/textures/GamingMainScene.jpg");
		m_Texture->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);

	}

	GameMainScene::~GameMainScene()
	{
	}

	void GameMainScene::SceneChangeController(GLFWwindow* window,Base*& currentScene, const std::vector<scene::Base*>& ScenesRegister)
	{
		glfwGetCursorPos(window, &xpos, &ypos);

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			std::cout << "GameMain: " << "x: " << xpos << "y: " << ypos << std::endl;
			if (xpos <= WIN_WIDTH/2)
			{
				currentScene = ScenesRegister[3];
			} 
			else
			{
				currentScene = ScenesRegister[4];
			}
		}
	}

	void GameMainScene::OnRender(Text& text)
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;

		m_Texture->Bind();

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Proj * m_View * model;

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			glm::mat4 mvp = m_Proj * m_View * model;

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}

	}

	void GameMainScene::OnUpdate()
	{

	}

}