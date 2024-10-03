#version 330 core
//A faire
// ajouter une variable uniform pour tous les sommets de type float permettant la mise à l'échelle
// ajouter une variable uniform pour tous les sommets de type vec3 permettant d'appliquer une translation au modèle
// i.e. a appliquer sur tous les sommets
//---------

//---------
// ajouter une variable o_color de type vec3 interpolée a envoyer au fragment shader

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
// A faire : ajouter un attribut de sommet color, contenant les couleurs pour chaque sommet à ( location = 1 )
//------
uniform float scale;
uniform vec3 translate;
layout(location = 1) in vec3 sommet_color;

out vec3 s_color; 

void main(){

    //Mettre à jour ce code pour appliquer la translation et la mise à l'échelle
    gl_Position =  vec4(scale * (vertexPosition_modelspace + translate) ,1);
    s_color = vec3(sommet_color);

    //Assigner la normale à la variable interpolée color
    //ajouter ici
}

