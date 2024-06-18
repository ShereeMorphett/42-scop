#version 330 core
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 FragColor;

void main()
{
    FragColor = vec4(fragTexCoord, 0.0, 1.0); // Simple color based on texture coordinates
}
