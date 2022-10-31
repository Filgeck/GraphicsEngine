#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 crntPos;

uniform vec4 lightColor;
uniform vec3 lightPos;

void main()
{
    FragColor = lightColor;
}