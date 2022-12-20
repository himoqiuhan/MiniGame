#pragma once
#include "Base.h"
#include <memory>

namespace scene
{
	class AllocationScene : public Base
	{
	public:
		AllocationScene();
		~AllocationScene();

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

		double xpos, ypos;
	};
}