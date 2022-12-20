#include "AllocationScene.h"

namespace scene
{

	AllocationScene::AllocationScene()
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

		m_Texture = std::make_unique<Texture>("res/textures/AllocScene.png");

		m_Shader->SetUniform1i("u_Texture", 0);

	}

	AllocationScene::~AllocationScene()
	{
	}

	void AllocationScene::SceneChangeController(GLFWwindow* window, Base*& currentScene, const std::vector<scene::Base*>& ScenesRegister, std::vector<Member>& member, std::vector<Mission>& mission)
	{
		glfwGetCursorPos(window, &xpos, &ypos);

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			if (xpos > 50 && xpos < 320 && ypos > 40 && ypos < 250)
			{

				std::cout << "Allocation: " << "x: " << xpos << "y: " << ypos << std::endl;
				currentScene = ScenesRegister[2];
			}
		}
	}

	void AllocationScene::OnRender(Text& text, std::vector<Member>& member,  std::vector<Mission>& mission)
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

	}

	void AllocationScene::OnUpdate()
	{

	}

}