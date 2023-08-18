#version 450 core
out vec4 FragColor;

in vec2 uv;

layout(binding=0) uniform sampler2D sampler;
uniform vec3 m_Color;

void main()
{
    FragColor = vec4(m_Color, 1.0) * texture(sampler, uv);
} 