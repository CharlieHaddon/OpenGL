#version 330
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
struct Lamp {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 colour;

uniform vec3 viewPos;
uniform Material material;
uniform Lamp lamp;

void main (){
    vec3 ambient = lamp.ambient * vec3 (texture (material.diffuse, TexCoords));
    
    vec3 normal = normalize (Normal);
    vec3 lightDir = normalize (lamp.position - FragPos);
    float diff = max (dot (normal, lightDir), 0);
    vec3 diffuse = lamp.diffuse * diff * 
        vec3 (texture (material.diffuse, TexCoords));

    vec3 viewDir = normalize (viewPos - FragPos);
    vec3 reflectDir = reflect (-lightDir, normal);
    float spec = pow (max (dot (viewDir, reflectDir), 0), material.shininess);
    vec3 specular = lamp.specular * spec * 
        vec3 (texture (material.specular, TexCoords));

    vec3 result = (ambient + diffuse + specular);
    colour = vec4 (result, 1.0f);
}
