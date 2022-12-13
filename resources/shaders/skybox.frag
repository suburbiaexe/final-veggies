#version 330 core
out vec4 fragColor;

in vec3 texCoords;

uniform samplerCube skybox;

void main()
{
    fragColor = texture(skybox, texCoords); // vec4(0.5, 0.5, 0.5, 1); //
}


//#version 330 core

//out vec4 fragColor;
//uniform float color;

//void main() {

//   if (color == 1) {
//       fragColor = vec4(1,1,1,1);
////       fragColor = vec4(0,0,0,0);
////       fragColor = vec4(0.98,0.85,0.38,1);
//   } else {
//       fragColor = vec4(0,0,0,0);
////       fragColor = vec4(1,1,1,1);
////       fragColor = vec4(0.98,0.85,0.38,1);
//   }
//}
