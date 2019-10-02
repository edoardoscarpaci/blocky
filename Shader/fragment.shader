#version 130

out vec3 color;
in vec3 colorpos;

void main(){
  color = vec3(clamp(colorpos.x,0,1),clamp(colorpos.y,0,1),clamp(colorpos.z,0,1));
}