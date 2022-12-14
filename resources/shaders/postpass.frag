#version 330 core
in vec3 uv;
uniform sampler2D occlusiontexture;

const float exposure = 0.3;
const float decay = 1.0;
const float density  = 1.0;
const float weight  = 0.01;

//const float exposure = 0.3;
//const float decay = 0.7;
//const float density  = 0.3;
//const float weight  = 0.2;

//const float exposure = 0.3f;
//const float decay = 0.96815;
//const float density  = 0.926;
//const float weight  = 0.587;

const int numSamples = 100 ;
uniform vec2 sunPos;

out vec4 fragColor;

void main(void)
{
    fragColor = vec4(0,0,0,0);
    vec2 deltaTextCoord = vec2(vec2(uv) - (3 * sunPos.xy) + 0.6);
    vec2 textCoo = uv.xy;
    deltaTextCoord *= (1.0 /  float(numSamples)) * density;
    float illuminationDecay = 1.0;
    for (int i = 0; i < numSamples; i++) {
        textCoo -= deltaTextCoord;
        vec3 samp = vec3(texture(occlusiontexture, textCoo));
        samp *= illuminationDecay * weight;
        fragColor += vec4(samp, 1);
        illuminationDecay *= decay;
    }
    fragColor *= exposure;


}
