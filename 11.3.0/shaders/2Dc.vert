#version 450
#extension GL_ARB_separate_shader_objects : enable

layout (binding = 0) uniform UniformBufferObject
{
  mat4 matrix;
} ubo;

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;

layout (location = 0) out vec3 fcolor;

void main ()
{
  gl_Position = ubo.matrix * vec4 (position, 0.f, 1.f);
  fcolor = color;
}
