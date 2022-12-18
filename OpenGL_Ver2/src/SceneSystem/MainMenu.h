#pragma once
#include "Base.h"
#include <memory>

namespace scene
{
	class MainMenu : public Base
	{
	public:
		MainMenu();
		~MainMenu();

		void SceneChangeController(GLFWwindow* window, Base*& currentScene, const std::vector<scene::Base*>& ScenesRegister) override;
		void OnRender() override;
		void OnUpdate() override;
	private:
		std::unique_ptr<VertexBuffer>m_VertexBuffer;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;

		glm::mat4 m_Proj, m_View;
		glm::vec3 m_TranslationA, m_TranslationB;

		double xpos, ypos;
	};
}