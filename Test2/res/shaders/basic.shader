#shader vertex

#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoords;

uniform mat4 u_MVP;
void main()
{
	gl_Position = position * u_MVP;
	v_TexCoords = texCoord;
}


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoords;
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoords);
	color = texColor;
}