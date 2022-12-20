#include "AssignmentScene.h"

namespace scene
{

	AssignmentScene::AssignmentScene()
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
		m_Shader->Bind();

		m_Texture = std::make_unique<Texture>("res/textures/AssignmentScene.png");
		m_Texture->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);

	}

	AssignmentScene::~AssignmentScene()
	{
	}

	void AssignmentScene::SceneChangeController(GLFWwindow* window, Base*& currentScene, const std::vector<scene::Base*>& ScenesRegister, std::vector<Member>& member, std::vector<Mission>& mission)
	{
		glfwGetCursorPos(window, &xpos, &ypos);

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (xpos > 20 && xpos < 520 && ypos > 900 && ypos < 1080)
		{
			m_TextColor = glm::vec3(1.0f, 1.0f, 1.0f);
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			{
				std::cout << "x: " << xpos << "y: " << ypos << std::endl;
				currentScene = ScenesRegister[1];
			}
		}
		else
		{
			m_TextColor = glm::vec3(0.5f, 0.8f, 1.0f);
		}

		if (xpos > 700 && xpos < 1200)
		{
			if (ypos > 180 && ypos < 300)
			{
				m_TextColorA = glm::vec3(0.5, 0.5, 0.5);
				if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
				{
					member[0].ChangeMission(mission[0].GetName());
					member[0].SetMood(100);
					mission[0].ChangeImpler("CH");
					mission[0].OnDoing();
					currentScene = ScenesRegister[3];
				}
			}
			else
				m_TextColorA = glm::vec3(0.0, 0.0, 0.0);

			if (ypos > 440 && ypos < 560)
			{
				m_TextColorB = glm::vec3(0.5, 0.5, 0.5);
				if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
				{
					member[1].ChangeMission(mission[1].GetName());
					member[1].SetMood(100);
					mission[1].ChangeImpler("MG");
					mission[1].OnDoing();
					currentScene = ScenesRegister[3];
				}
			}
			else
				m_TextColorB = glm::vec3(0.0, 0.0, 0.0);

			if (ypos > 680 && ypos < 800)
			{
				m_TextColorC = glm::vec3(0.5, 0.5, 0.5);
				if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
				{
					member[2].ChangeMission(mission[2].GetName());
					member[2].SetMood(100);
					mission[2].ChangeImpler("CX");
					mission[2].OnDoing();
					currentScene = ScenesRegister[3];
				}
			}
			else
				m_TextColorC = glm::vec3(0.0, 0.0, 0.0);
		}
		else
		{
			m_TextColorA = glm::vec3(0.0, 0.0, 0.0);
			m_TextColorB = glm::vec3(0.0, 0.0, 0.0);
			m_TextColorC = glm::vec3(0.0, 0.0, 0.0);
		}
	}

	void AssignmentScene::OnRender(Text& text, std::vector<Member>& member,  std::vector<Mission>& mission)
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;

		m_Texture->Bind();

		{
			//background rendering
			m_Texture->Bind();
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
			text.RenderText("Back", 160.0f, 60.0f, 1.0f, m_TextColor);

			text.RenderText(mission[0].GetName(), 700.0f, 800.0f, 1.0f, m_TextColorA);
			text.RenderText(mission[0].GetImpler(), 1400.0f, 800.0f, 1.0f, m_TextColorA);

			text.RenderText(mission[1].GetName(), 700.0f, 550.0f, 1.0f, m_TextColorB);
			text.RenderText(mission[1].GetImpler(), 1400.0f, 550.0f, 1.0f, m_TextColorB);

			text.RenderText(mission[2].GetName(), 700.0f, 300.0f, 1.0f, m_TextColorC);
			text.RenderText(mission[2].GetImpler(), 1400.0f, 300.0f, 1.0f, m_TextColorC);
		}

	}

	void AssignmentScene::OnUpdate()
	{

	}

}