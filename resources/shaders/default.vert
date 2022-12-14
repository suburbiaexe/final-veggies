#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 texcoords;

out vec4 worldspacepos;
out vec4 worldspacenorm;

uniform mat4 modelmat;
uniform mat4 viewmat;
uniform mat4 projmat;
uniform mat3 invTransposeModel;
uniform float sun;

out vec3 uv;

void main() {
   uv = position;
   worldspacepos = modelmat * vec4(position, 1.0);
   worldspacenorm = vec4(invTransposeModel * normal, 0.0);

   if (sun == 1) {
       gl_Position = projmat * viewmat * modelmat * vec4(position, 1.0);
   } else {
       gl_Position = projmat * viewmat * modelmat * vec4(position, 1.0);
   }

}
