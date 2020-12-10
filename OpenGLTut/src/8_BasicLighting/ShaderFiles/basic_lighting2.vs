#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // the model here is a Identity matrix
    // aPos is the position of a vertex
    // -> get the position of the considered vertex as the fragment's position vector
    FragPos = vec3(model * vec4(aPos, 1.0));

    // In case, the model vector contains: scale, rotate
    // -> need to get the Normal vector in the new coordinate system
    Normal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}