#version 330

layout(location = 0) in vec3 in_position; 
layout(location = 1) in vec3 in_normal; 
layout(location = 2) in vec2 in_texcoord; 
uniform mat4 model_matrix, view_matrix, projection_matrix; 
out vec3 world_pos; 
out vec3 world_normal; 
out vec2 texcoord; 
out vec4 viewSpace; 

void main(){ 
//used for lighting models 
world_pos = (model_matrix * vec4(in_position,1)).xyz; 
world_normal = normalize(mat3(model_matrix) * in_normal); 
texcoord = in_texcoord; 
//send it to fragment shader 
viewSpace = view_matrix * model_matrix * vec4(in_position,1); 
gl_Position = projection_matrix * viewSpace; 
}
