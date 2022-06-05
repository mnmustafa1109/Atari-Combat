#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;
uniform mat4 projection1;
uniform mat4 view1;

void main()
{
gl_Position = projection1 *view1* vec4(vertex.xy, 1.0, 1.0);
TexCoords = vertex.zw;
}