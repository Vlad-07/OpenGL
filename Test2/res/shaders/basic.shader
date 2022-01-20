#shader vertex

#version 330 core

layout(location = 0) in vec4 position;

uniform vec4 offset;

void main()
{
	gl_Position = position + offset;
}


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
	color = u_Color;
}