#version 450
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in vec4 position;

layout (location = 0) out vec2 textcoord;

void main ()
{
  gl_Position = vec4 (position.xy, 0.f, 1.f);
  textcoord = position.zw;
}
