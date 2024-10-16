#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertices_position_modelspace;

//TODO create uniform transformations matrices Model View Projection
// Values that stay constant for the whole mesh.

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

void main(){
        // TODO : Output position of the vertex, in clip space : MVP * position
        gl_Position = projection * view * transform * vec4(vertices_position_modelspace,1);
}

