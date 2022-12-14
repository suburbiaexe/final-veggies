//#version 330 core

//// Task 15: add a second layout variable representing a UV coordinate
//layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 normal;

//// Task 16: create an "out" variable representing a UV coordinate
//out vec3 uv;

//uniform mat3 invTransposeModel;
//uniform mat4 modelmat;
//uniform mat4 viewmat;
//uniform mat4 projmat;

//void main() {
//    // Task 16: assign the UV layout variable to the UV "out" variable
//    uv = position;

//    gl_Position = projmat * viewmat * vec4(position, 1.0);
//}


#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
//layout (location = 2) in vec3 color;

out vec4 worldspacepos;
out vec4 worldspacenorm;

uniform mat4 modelmat;
uniform mat4 viewmat;
uniform mat4 projmat;
uniform mat3 invTransposeModel;
uniform float sun;

//out vec3 outcolor;

void main() {
//   outcolor = color;
   worldspacepos = modelmat * vec4(position, 1.0);
   worldspacenorm = vec4(invTransposeModel * normal, 0.0);

   if (sun == 1) {
       gl_Position = projmat * viewmat * modelmat * vec4(position, 1.0);
   } else {
       gl_Position = projmat * viewmat * modelmat * vec4(position, 1.0);
   }

}
