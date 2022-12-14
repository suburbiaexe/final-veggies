#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 texCoords;

uniform mat4 projmat;
uniform mat4 viewmat;

void main()
{
//    vec4 pos = projmat * viewmat * vec4(aPos, 1.0f);
//    // Having z equal w will always result in a depth of 1.0f
////    gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
//    gl_Position = projmat * viewmat * vec4(aPos, 1.0);
//    // We want to flip the z axis due to the different coordinate systems (left hand vs right hand)
//    texCoords = vec3(aPos.x, aPos.y, -aPos.z);

    texCoords = aPos;
    gl_Position = projmat * viewmat * vec4(aPos, 1.0);

    //vec4(texCoords, 1);//
}

