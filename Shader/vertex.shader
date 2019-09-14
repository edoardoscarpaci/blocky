#version 130
in vec3 pos;
in vec2 uv;

uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position =  projection * view* vec4(pos,1) ;

}