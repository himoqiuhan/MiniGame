#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

out vec2 v_TexCoord;

void main()
{
	vec4 edge = {postion.x * 1.1, position.y * 1.1, 1.0f, 1.0f}
	gl_Position = u_MVP * position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
	color = u_Color;
};