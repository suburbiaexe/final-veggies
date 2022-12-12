#version 330 core
/// Our light scattering pass texture
uniform sampler2D occlusiontexture;
/// Indicate where is the light source on the screen (2D position)
uniform vec2 sunPos;

in vec3 uv;

out vec4 fragColor;
void main()
{
 float decay=0.96815;
 float exposure=0.2;
 float density=0.926;
 float weight=0.58767;
 /// NUM_SAMPLES will describe the rays quality, you can play with
 int NUM_SAMPLES = 100;
 vec2 tc = vec2(uv); //gl_TexCoord[0].xy;
// vec2 deltaTexCoord = tc — sunPos.xy;
 vec2 deltaTexCoord = tc - sunPos;
 deltaTexCoord *= 1.0 / float(NUM_SAMPLES) * density;
 float illuminationDecay = 1.0;
 vec4 color =texture(occlusiontexture, tc.xy)*0.4;
 for(int i=0; i < NUM_SAMPLES ; i++)
 {
    tc -= deltaTexCoord;
    vec4 sample = texture(occlusiontexture, tc)*0.4;
    sample *= illuminationDecay * weight;
    color += sample;
    illuminationDecay *= decay;
 }
 fragColor = color;
}






//#version 330 core
//in vec3 uv;
//uniform sampler2D occlusiontexture;

////const float exposure = 0.3f;
////const float decay = 0.96815;
////const float density  = 0.926;
////const float weight  = 0.4;
////const float weight  = 0.587;

//const float exposure = 1.0;
//const float decay = 1.0;
//const float density  = 1.0;
//const float weight  = 0.01;

//const int numSamples = 100 ;
//uniform vec2 sunPos; // need to figure this out - this is wrong for sure

//out vec4 fragColor;

//void main(void)
//{
////    fragColor = vec4(0,0,0,0);
////    vec2 deltaTextCoord = vec2( uv.xy - sunPos.xy );
////    vec2 textCoo = uv.xy;
////    deltaTextCoord *= 1.0 /  float(numSamples) * density;
////    float illuminationDecay = 1.0;


////    for(int i=0; i < numSamples ; i++)
////    {
////             textCoo -= deltaTextCoord;
////             vec4 samp = texture(occlusiontexture, textCoo);

////             samp *= illuminationDecay * weight;

////             fragColor += samp;

////             illuminationDecay *= decay;
////     }
////     fragColor *= exposure;



//    fragColor = vec4(0,0,0,0);
//    //(sunPos.xy * 0.5 + 0.5)
//    vec2 deltaTextCoord = vec2(vec2(uv) - (3 * sunPos.xy) + 0.6);
//    vec2 textCoo = uv.xy;
//    deltaTextCoord *= (1.0 /  float(numSamples)) * density;
//    float illuminationDecay = 1.0;
//    for (int i = 0; i < numSamples; i++) {
//        textCoo -= deltaTextCoord;
//        vec3 samp = vec3(texture(occlusiontexture, textCoo));
//        samp *= illuminationDecay * weight;
//        fragColor += vec4(samp, 1);
//        illuminationDecay *= decay;
//    }
//    fragColor *= exposure;


////    int NUM_SAMPLES = 80;
////    vec2 tc = vec2(uv);
////    vec2 deltatexCoord = (tc - (sunPos.xy*0.5 + 0.5));
////    deltatexCoord *= 1.0/ float(numSamples);
////    float illuminationDecay = 1.0f;

////    vec4 godRayColor = texture(occlusiontexture , tc.xy)*0.4;
////    for(int i = 0 ; i< numSamples ; i++)
////    {
////            tc-= deltatexCoord;
////            vec4 samp = texture(occlusiontexture , tc )*0.4;
////            samp *= illuminationDecay*weight;
////            godRayColor += samp;
////            illuminationDecay *= decay;
////    }
////    vec4 realColor = texture(occlusiontexture , vec2(uv));
////    fragColor = ((vec4((vec3(godRayColor.r, godRayColor.g, godRayColor.b) * exposure), 1)) + (realColor*(1.0)));

//}
