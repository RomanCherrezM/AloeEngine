#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNor;
layout (location = 2) in vec2 aUV;

uniform mat4 m_Transform;
uniform mat4 m_View;
uniform mat4 m_Projection;

out vec3 color;

void main()
{
    color = aNor;

    gl_Position = m_Projection * m_View * m_Transform * vec4(aPos, 1.0);
}