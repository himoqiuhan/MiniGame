#pragma once
#include "GL/glew.h"

#include "glm/detail/glm.cpp"
#include "glm/gtc/matrix_transform.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <iostream>

#include "Shader.h"


struct Character
{
	GLuint TextureID;	// ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance; // Horizontal offset to advance to next glyph
};

class Text
{
private:
	std::map<GLchar, Character> Characters;
	GLuint m_VAO, m_VBO;
	Shader m_Shader;
public:
	Text();
	~Text();

	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
};
