#version 330
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

void main (){
    FragPos = vec3 (modelMatrix * vec4 (position, 1.0f));
    Normal = mat3 (transpose (inverse (modelMatrix))) * normal;
    TexCoords = texCoords;
    gl_Position = projectionMatrix 
                * viewMatrix 
                * modelMatrix 
                * vec4 (position, 1.0);
}
