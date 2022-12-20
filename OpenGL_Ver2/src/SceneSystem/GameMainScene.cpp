#include "GameMainScene.h"

namespace scene
{

	GameMainScene::GameMainScene()
		:m_Proj(glm::ortho(0.0f, 2.0f, 0.0f, 2.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{
		float positions[] = {
			-1.0f, -1.0f, 0.0f, 0.0f, //0
			 1.0f, -1.0f, 1.0f, 0.0f, //1
			 1.0f,  1.0f, 1.0f, 1.0f, //2
			-1.0f,  1.0f, 0.0f, 1.0f, //3
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

		m_TextureBackground = std::make_unique<Texture>("res/textures/GameMainScene.png");
		m_TextureA = std::make_unique<Texture>("res/textures/TextureA.png");
		m_TextureB = std::make_unique<Texture>("res/textures/TextureB.png");
		m_TextureC = std::make_unique<Texture>("res/textures/TextureC.png");

		m_Shader->SetUniform1i("u_Texture", 0);

	}

	GameMainScene::~GameMainScene()
	{
	}

	void GameMainScene::SceneChangeController(GLFWwindow* window, Base*& currentScene, const std::vector<scene::Base*>& ScenesRegister, std::vector<Member>& member, std::vector<Mission>& mission)
	{
		glfwGetCursorPos(window, &xpos, &ypos);

		if (xpos > 85 && xpos < 610 && ypos > 30 && ypos < 120)
		{
			m_TextColor = glm::vec3(1.0f, 1.0f, 1.0f);
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			{
				std::cout << "x: " << xpos << "y: " << ypos << std::endl;
				currentScene = ScenesRegister[2];
			}
		}
		else
		{
			m_TextColor = glm::vec3(0.89f, 0.59f, 0.12f);
		}


		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

	}

	void GameMainScene::OnRender(Text& text, std::vector<Member>& member,  std::vector<Mission>& mission)
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;

		m_TextureBackground->Bind();

		{
			//background rendering
			m_TextureBackground->Bind();
			m_Proj = glm::ortho(0.0f, 2.0f, 0.0f, 2.0f, -1.0f, 1.0f);
			m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
			model = glm::translate(glm::mat4(1.0f), glm::vec3(1, 1, 0));
			mvp = m_Proj * m_View * model;

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}

		{
			//Text rendering
			text.RenderText("Assignment", 240.0f, 990.0f, 0.5f, m_TextColor);
		}

		if (ypos > 200 && ypos < 380)
		{
			if (xpos > 380 && xpos < 520)
			{
				m_TextureA->Bind();
				m_Proj = glm::ortho(0.0f, 26.0f, 0.0f, 6.0f, -1.0f, 1.0f);
				m_View = glm::translate(glm::mat4(1.0f), glm::vec3(3, 1.5, 0));
				model = glm::translate(glm::mat4(1.0f), glm::vec3(1, 1, 0));
				mvp = m_Proj * m_View * model;

				m_Shader->Bind();
				m_Shader->SetUniformMat4f("u_MVP", mvp);

				renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);

				text.RenderText(member[0].GetMission(), 400.0f, 550.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
				text.RenderText(member[0].GetMood(), 400.0f, 300.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
			}
			if (xpos > 830 && xpos < 1010)
			{
				m_TextureB->Bind();
				m_Proj = glm::ortho(0.0f, 26.0f, 0.0f, 6.0f, -1.0f, 1.0f);
				m_View = glm::translate(glm::mat4(1.0f), glm::vec3(9.3, 1.5, 0));
				model = glm::translate(glm::mat4(1.0f), glm::vec3(1, 1, 0));
				mvp = m_Proj * m_View * model;

				m_Shader->Bind();
				m_Shader->SetUniformMat4f("u_MVP", mvp);

				renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);

				text.RenderText(member[1].GetMission(), 860.0f, 550.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
				text.RenderText(member[1].GetMood(), 860.0f, 300.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
			}
			if (xpos > 1300 && xpos < 1480)
			{
				m_TextureC->Bind();
				m_Proj = glm::ortho(0.0f, 26.0f, 0.0f, 6.0f, -1.0f, 1.0f);
				m_View = glm::translate(glm::mat4(1.0f), glm::vec3(15.6, 1.5, 0));
				model = glm::translate(glm::mat4(1.0f), glm::vec3(1, 1, 0));
				mvp = m_Proj * m_View * model;

				m_Shader->Bind();
				m_Shader->SetUniformMat4f("u_MVP", mvp);

				renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);

				text.RenderText(member[2].GetMission(), 1350.0f, 550.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
				text.RenderText(member[2].GetMood(), 1350.0f, 300.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
			}
		}

	}

	void GameMainScene::OnUpdate()
	{

	}

}