//#version 330 core
//in vec3 uv;
//uniform mat4 projmat;
//uniform mat4 viewmat;
//out vec3 texcoords;

//void main() {
//  texcoords = uv;
//  gl_Position = projmat * viewmat * vec4(uv, 1.0);
//}







//layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 normal;

//out vec4 worldspacepos;
//out vec4 worldspacenorm;

//uniform mat4 modelmat;
//uniform mat4 viewmat;
//uniform mat4 projmat;
//uniform mat3 invTransposeModel;
//uniform float sun;

//void main() {
//   worldspacepos = modelmat * vec4(position, 1.0);
//   worldspacenorm = vec4(invTransposeModel * normal, 0.0);

//   if (sun == 1) {
//       gl_Position = projmat * viewmat * modelmat * vec4(position, 1.0);
//   } else {
//       gl_Position = projmat * viewmat * modelmat * vec4(position, 1.0);
//   }
//   gl_Position = vec4(position, 1);

//}


#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 texCoords;

uniform mat4 projmat;
uniform mat4 viewmat;
//uniform mat4 modelmat;

void main()
{
//    vec4 pos = projmat * viewmat * vec4(aPos, 1.0f);
//    // Having z equal w will always result in a depth of 1.0f
////    gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
//    gl_Position = projmat * viewmat * vec4(aPos, 1.0);
//    // We want to flip the z axis due to the different coordinate systems (left hand vs right hand)
//    texCoords = vec3(aPos.x, aPos.y, -aPos.z);

    texCoords = aPos;
    gl_Position = projmat * viewmat * vec4(aPos, 1.0); //vec4(texCoords, 1);//
}

