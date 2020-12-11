#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 LightingColor; // resulting color from lighting calculations

// Put all the calculation variables into vertex shader instead of fragment shader
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

// the variables for transformation between spaces
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);

    // gouraud shading
    vec3 Position = vec3(model * vec4(aPos, 1.0f)); // translate the vertex position of the object into world space by model matrix
    vec3 Normal = mat3(transpose(inverse(model))) * aNormal; // get the Normal vector in case the local space is scaled or rotate (if the vertices are linearly transform, the transpose maybe redundant)

    // ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - Position); // get the light direction from the difference between Light's position vector and Vertex's positon vector
    float diff = max(dot(norm, lightDir), 0.0f); // the dot product represent the magnitude of perpendicular projection of one vector on the other one -> describe how large the reflection of the light to camera position
    vec3 diffuse = diff * lightColor;

    // specular
    float specularStrength = 1.0f; // this is set higher to better show the effect of Gouraud shading
    vec3 viewDir = normalize(viewPos - Position);
    vec3 reflectDir = reflect(-lightDir, norm); // get the reflect vector from the light source, through normal vector standing on the vertex, to the camera position
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // this describe the magnitude of reflection from light source to camera (or viewer position)
    vec3 specular = specularStrength * spec * lightColor;

    LightingColor = ambient + diffuse + specular;
}

/*
So what do we see?
You can see (for yourself or in the provided image) the clear distinction of the two triangles at the front of the 
cube. This 'stripe' is visible because of fragment interpolation. From the example image we can see that the top-right 
vertex of the cube's front face is lit with specular highlights. Since the top-right vertex of the bottom-right triangle is 
lit and the other 2 vertices of the triangle are not, the bright values interpolates to the other 2 vertices. The same 
happens for the upper-left triangle. Since the intermediate fragment colors are not directly from the light source 
but are the result of interpolation, the lighting is incorrect at the intermediate fragments and the top-left and 
bottom-right triangle collide in their brightness resulting in a visible stripe between both triangles.

This effect will become more apparent when using more complicated shapes.
*/