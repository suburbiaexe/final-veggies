#version 330 core

out vec4 fragColor;
uniform float color;

void main() {

   if (color == 1) {
       fragColor = vec4(1,1,1,1);
   } else {
       fragColor = vec4(0.6,0.6,0,0);
   }
}
