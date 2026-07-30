#version 450
#extension GL_ARB_separate_shader_objects : enable

layout (binding = 0) uniform sampler2D texture_image;

layout (location = 0) out vec2 t_position;
layout (location = 1) out vec4 out_color;

void main ()
{
  out_color = texture (texture_image, t_position);
}
