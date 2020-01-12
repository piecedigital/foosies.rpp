// http://in2gpu.com/2014/06/23/toon-shading-effect-and-simple-contour-detection/
// Phong Reflection Model Vertex Shader

#version 330

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec2 vertexTexCoord;

uniform mat4 model_matrix, view_matrix, projection_matrix;

//send them to fragment shader
out vec3 world_pos;
out vec3 world_normal;
out vec2 fragTexCoord;

void main()
{
    //convert in world coords
    world_pos = mat3(model_matrix) * vertexPosition;//careful here
    world_normal = normalize(mat3(model_matrix) * vertexNormal);

    fragTexCoord = vertexTexCoord;

    gl_Position = projection_matrix*view_matrix*model_matrix*vec4(vertexPosition,1);
}
