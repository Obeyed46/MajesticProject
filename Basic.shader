#vertex shader
#version 330 core\n
\n
layout(location = 0) in vec4 position; \n
\n
void main()\n
{ \n
gl_postion = position; \n
}\n;

#fragmentshader
#version 330 core\n
\n
layout(location = 0) out vec4 color; \n
\n
void main()\n
{ \n
color = vec4(1.0 , 1.0 , 0.0 , 1.0); \n
}\n;