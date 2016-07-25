#version 330
in vec3 Normal;
in vec3 FragPos;

out vec4 colour;

uniform vec3 objectColour;
uniform vec3 lightColour;
uniform vec3 lampPos;
uniform vec3 viewPos;

void main (){
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColour;

    vec3 normal = normalize (Normal);
    vec3 lightDir = normalize (lampPos - FragPos);

    float diff = max (dot (normal, lightDir), 0);
    vec3 diffuse = diff * lightColour;

    float specularStrength = 0.5f;
    vec3 viewDir = normalize (viewPos - FragPos);
    vec3 reflectDir = reflect (-lightDir, normal);
    
    float spec = pow (max (dot (viewDir, reflectDir), 0), 32);
    vec3 specular = specularStrength * spec * lightColour;

    vec3 result = (ambient + diffuse + specular) * objectColour;

    colour = vec4 (result, 1.0f);
}
