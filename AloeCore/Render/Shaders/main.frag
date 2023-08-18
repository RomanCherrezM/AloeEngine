#version 450 core
out vec4 FragColor;
  
in vec2 uv;

layout(binding=0) uniform sampler2D sampler;

void main()
{
    FragColor = texture(sampler, uv);
} 