#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 uvcoord;

out vec3 uv;

void main(void)
{
//    uv = 0.5 * (position + 1.0);
    uv = uvcoord;
//    gl_Position = vec4(position, 1.0);
    gl_Position = vec4(position.xy, 0.0, 1.0);

//    vUv = 0.5 * (position+1.0);

  //  gl_Position = vec4(position.xy, 0.0, 1.0);
//    gl_Position = projmat * viewmat * modelmat * vec4(position, 1.0);
}
