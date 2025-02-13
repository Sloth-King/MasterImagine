#version 330 core



// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertices_position_modelspace;
layout(location = 1) in vec4 vertex_color;
out vec4 o_color;
//TODO create uniform transformations matrices Model View Projection
// Values that stay constant for the whole mesh.
uniform mat4 transformations;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main(){

        // TODO : Output position of the vertex, in clip space : MVP * position
        gl_Position = projectionMatrix*viewMatrix*transformations*vec4(vertices_position_modelspace,1);
        o_color = vertex_color;
}

