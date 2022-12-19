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

#include <iostream>
#include <vector>
#include <functional>

namespace scene
{
	class Base
	{
	public:
		Base(){}
		virtual ~Base(){}

		virtual void SceneChangeController(GLFWwindow* window, Base*& currentScene, const std::vector<scene::Base*>& ScenesRegister) {}
		virtual void OnRender(Text& text) {}
		virtual void OnUpdate() {}
	};
}