#version 330 core

out vec4 fragColor;
uniform float color;

void main() {

   if (color == 1) {
       fragColor = vec4(1,1,1,1);
//       fragColor = vec4(0,0,0,0);
//       fragColor = vec4(0.98,0.85,0.38,1);
   } else {
       fragColor = vec4(0,0,0,0);
//       fragColor = vec4(1,1,1,1);
//       fragColor = vec4(0.98,0.85,0.38,1);
   }
}
