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
    // [datvt] calculate the fragment's position by model matrix (scale -> rotate. not translation)
    //         pass this value to fragment shader to calculate the light direction from the light source to the fragment
    FragPos = vec3(model * vec4(aPos, 1.0));

    // [datvt] get the normal vector. this is stored in tthe vertices matrix in the simple examples, 
    //         but in terms of complicated ones, we might have to calculate it
    Normal = aNormal;  
    
    // because the FragPos = fragment's position transformed with model matrix -> fragment in the world space
    // => projection * view * vec4(FragPos, 1.0) = projection * view * model * vec4(aPos, 1.0)
    // => save redundant calculations
    gl_Position = projection * view * vec4(FragPos, 1.0);
}