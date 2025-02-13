#version 330 core

// Output data
// in vec4 o_color;
out vec4 color;

uniform vec3 objet_couleur;

void main()
{

    // Mettre à jour la couleur avec la variable interpolée venant du vertex shader
    color = vec4(objet_couleur,1.f);// Output color = red

}