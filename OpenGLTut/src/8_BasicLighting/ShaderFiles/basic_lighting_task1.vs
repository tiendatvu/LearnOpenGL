#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;
out vec3 LightPos;

// we now define the uniform (which contains light source's position vector) in the vertex shader, instead of fragment shader
// and pass the 'view space' light position
// at the beginning, the lightPos should be at the WORLD SPACE -> need to be transformed to VIEW SPACE by View matrix
uniform vec3 lightPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    
    // Now, the Fragment's position is tranformed into the VIEW SPACE too
    FragPos = vec3(view * model * vec4(aPos, 1.0f));
    
    // Because the obejct is transformed into VIEW SPACE -> it's vertex is also transformed, and for almost cases, NON-LINEAR TRANSFORMED
    // -> the normal vector need to be applied the below algorithm -> get a new NORMAL VECTOR in the VIEW SPACE
    Normal = mat3(transpose(inverse(view * model))) * aNormal;

    // Transform world space light position to view space light position
    // get the top 3 components to form a vec3 vector
    LightPos = vec3(view * vec4(lightPos, 1.0));
}