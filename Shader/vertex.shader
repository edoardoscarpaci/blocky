#version 130
in vec3 pos;
in vec2 uv;

uniform mat4 view;
uniform mat4 projection;

out vec3 colorpos;

void main(){
    gl_Position =  projection * view *  vec4(pos,1) ;
    colorpos = pos;

}