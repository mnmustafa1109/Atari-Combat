#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 vertexColor;

uniform mat4 transform; 

void main(){
   // gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
   vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);
}