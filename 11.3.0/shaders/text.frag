#version 450
#extension GL_ARB_separate_shader_objects : enable

layout (binding = 0) uniform sampler2D text;
layout (binding = 1) uniform UniformBufferObject
{
  vec4 color;
} ubo;

layout (location = 0) out vec2 textcoord;
layout (location = 1) out vec4 out_color;

void main ()
{
  out_color = vec4 (1.f, 1.f, 1.f, texture (text, textcoord).a) * ubo.color;
}
