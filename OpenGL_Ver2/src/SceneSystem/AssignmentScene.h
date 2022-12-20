#pragma once
#include "Base.h"
#include <memory>

namespace scene
{
	class AssignmentScene : public Base
	{
	public:
		AssignmentScene();
		~AssignmentScene();

		void SceneChangeController(GLFWwindow* window, Base*& currentScene, const std::vector<scene::Base*>& ScenesRegister,std::vector<Member>& member,  std::vector<Mission>& mission) override;
		void OnRender(Text& text, std::vector<Member>& member,  std::vector<Mission>& mission) override;
		void OnUpdate() override;
	private:
		std::unique_ptr<VertexBuffer>m_VertexBuffer;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;

		glm::mat4 m_Proj, m_View, model, mvp;

		glm::vec3 m_TextColor = glm::vec3(0.5f, 0.8f, 1.0f);

		glm::vec3 m_TextColorA = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_TextColorB = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_TextColorC = glm::vec3(0.0f, 0.0f, 0.0f);

		double xpos, ypos;
	};
}