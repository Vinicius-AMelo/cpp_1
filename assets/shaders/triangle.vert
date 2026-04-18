#version 330 core

layout (location = 0) in vec3 aPos;

uniform vec2 uOffset;
vec3 displacedPos;

void main()
{
    displacedPos = vec3(aPos.x + uOffset.x, aPos.y + uOffset.y, aPos.z);
    gl_Position = vec4(displacedPos, 1.0);
}
