#version 450
#extension GL_ARB_separate_shader_objects : enable

layout (binding = 0) uniform UniformBufferObject
{
  vec3 color;
  mat4 matrix;
} ubo;

layout (location = 0) in vec3 position;

layout (location = 0) out vec3 fcolor;

void main ()
{
  gl_Position = ubo.matrix * vec4 (position, 1.f);
  fcolor = ubo.color;
}
