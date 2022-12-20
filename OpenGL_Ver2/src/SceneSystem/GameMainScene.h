#pragma once
#include "Base.h"
#include <memory>

namespace scene
{
	class GameMainScene : public Base
	{
	public:
		GameMainScene();
		~GameMainScene();

		void SceneChangeController(GLFWwindow* window, Base*& currentScene, const std::vector<scene::Base*>& ScenesRegister,std::vector<Member>& member,  std::vector<Mission>& mission) override;
		void OnRender(Text& text, std::vector<Member>& member,  std::vector<Mission>& mission) override;
		void OnUpdate() override;
	private:
		std::unique_ptr<VertexBuffer>m_VertexBuffer;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_TextureBackground;

		std::unique_ptr<Texture> m_TextureA;
		std::unique_ptr<Texture> m_TextureB;
		std::unique_ptr<Texture> m_TextureC;

		glm::mat4 m_Proj, m_View, model, mvp;

		glm::vec3 m_TextColor = glm::vec3(0.89f, 0.59f, 0.12f);

		double xpos, ypos;

	};
}