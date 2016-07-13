#version 330
in vec2 TexCoord;

out vec4 colour;

uniform sampler2D uniTexture;

void main (){
    colour = texture (uniTexture, TexCoord);
}
