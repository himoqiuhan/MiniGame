#include "MainMenu.h"

namespace scene
{

	MainMenu::MainMenu()
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
		m_ShaderBack = std::make_unique<Shader>("res/shaders/Framework.shader");

		m_TextureBackgound = std::make_unique<Texture>("res/textures/MainMenu.png");
		m_TextureButton = std::make_unique<Texture>("res/textures/Button.jpg");

	}

	MainMenu::~MainMenu()
	{
	}

	void MainMenu::SceneChangeController(GLFWwindow* window,Base*& currentScene, const std::vector<scene::Base*>& ScenesRegister)
	{
		glfwGetCursorPos(window, &xpos, &ypos);

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			std::cout << "Menu: " << "x: " << xpos << "y: " << ypos << std::endl;
			if (xpos > 150 && xpos < 550)
			{
				if (ypos < 620 && ypos > 470)
				{
					currentScene = ScenesRegister[1];
				}
				if (ypos < 950 && ypos > 800)
				{
					glfwSetWindowShouldClose(window, true);
				}
			}
		}
	}

	void MainMenu::OnRender(Text& text)
	{
		GLCall(glClearColor(0.2f, 0.3f, 1.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;

		{
			//background rendering
			m_TextureBackgound->Bind();
			m_Proj = glm::ortho(0.0f, 2.0f, 0.0f, 2.0f, -1.0f, 1.0f);
			m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
			model = glm::translate(glm::mat4(1.0f), glm::vec3(1, 1, 0));
			mvp = m_Proj * m_View * model;

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}

		if(xpos > 150 && xpos < 550)
		{
			if (ypos < 620 && ypos > 470)
			{
				m_TextureBackgound->Unbind();
				m_Proj = glm::ortho(0.0f, 8.0f, 0.0f, 10.0f, -1.0f, 1.0f);
				m_View = glm::translate(glm::mat4(1.0f), glm::vec3(1.5, 3.4, 0));
	
				model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 1.5, 0));
				mvp = m_Proj * m_View * model;
				m_ShaderBack->Bind();
				m_ShaderBack->SetUniformMat4f("u_MVP", mvp);
				m_ShaderBack->SetUniform4f("u_Color", glm::vec4(0.5f, 0.8f, 1.0f,1.0f));
				renderer.Draw(*m_VAO, *m_IndexBuffer, *m_ShaderBack);
			}
			else if (ypos < 950 && ypos > 800)
			{
				m_TextureBackgound->Unbind();
				m_Proj = glm::ortho(0.0f, 8.0f, 0.0f, 10.0f, -1.0f, 1.0f);
				m_View = glm::translate(glm::mat4(1.0f), glm::vec3(1.5, 3.4, 0));

				model = glm::translate(glm::mat4(1.0f), glm::vec3(0, -1.5, 0));
				mvp = m_Proj * m_View * model;
				m_ShaderBack->Bind();
				m_ShaderBack->SetUniformMat4f("u_MVP", mvp);
				m_ShaderBack->SetUniform4f("u_Color", glm::vec4(0.5f, 0.8f, 1.0f,1.0f));
				renderer.Draw(*m_VAO, *m_IndexBuffer, *m_ShaderBack);
			}
		}

		{
			//button rendering
			m_TextureButton->Bind();
			m_Proj = glm::ortho(0.0f, 8.0f, 0.0f, 10.0f, -1.0f, 1.0f);
			m_View = glm::translate(glm::mat4(1.0f), glm::vec3(1.5, 3.5, 0));

			model = glm::translate(glm::mat4(1.0f), glm::vec3(0,1.5,0));
			mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);

			model = glm::translate(glm::mat4(1.0f), glm::vec3(0, -1.5, 0));
			mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}

		{
			//Text
			text.RenderText("Begin", 250.0f, 510.0f, 1.0f, glm::vec3(0.2f, 0.5f, 1.0f));
			text.RenderText("Exit", 275.0f, 180.0f, 1.0f, glm::vec3(0.2f, 0.5f, 1.0f));
			text.RenderText("ChikaChikaBanBan", 700.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
		}

	}

	void MainMenu::OnUpdate()
	{

	}

}