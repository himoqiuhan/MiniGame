#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Renderer.hpp"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "TextRender.h"

#include "glm/detail/glm.cpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Mission.h"
#include "Teammate.h"

#include <iostream>
#include <string>
#include <vector>
#include <functional>

namespace scene
{
	class Base
	{
	public:
		Base(){}
		virtual ~Base(){}

		virtual void SceneChangeController(GLFWwindow* window, Base*& currentScene, const std::vector<scene::Base*>& ScenesRegister,std::vector<Member>& member,  std::vector<Mission>& mission) {}
		virtual void OnRender(Text& text, std::vector<Member>& member,  std::vector<Mission>& mission) {}
		virtual void OnUpdate() {}
	};
}