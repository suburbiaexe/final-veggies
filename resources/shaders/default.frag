#version 330 core

in vec4 worldspacenorm;
in vec4 worldspacepos;

out vec4 fragColor;

uniform float ka;
uniform float kd;
uniform float ks;

uniform float shininess;
uniform vec4 camerapos;

uniform vec4 lightcolor[8];
uniform vec4 lightdir[8];

uniform vec4 cambient;
uniform vec4 cdiffuse;
uniform vec4 cspecular;

uniform vec4 lightpos[8];
uniform vec3 function[8];

uniform float type[8];

uniform float outerangle[8];
uniform float innerangle[8];

uniform float lightsize;
uniform int terrain;

in vec3 outcolor;

void main() {
    if (terrain == 1) {
//        fragColor = vec4(outcolor, 1);
        fragColor = vec4(1);
    } else {
        vec4 worldspacenorm = normalize(worldspacenorm);

        fragColor = vec4(0.0);

        vec4 ambient = ka * cambient;
        fragColor += ambient;
        float attenuation = 1;

        for (int i = 0; i < lightsize; i++) {
            vec4 lightDir;
            vec4 intensity = lightcolor[i];
            if (type[i] == 0.0) {
                // directional
                lightDir = normalize(-lightdir[i]);
            } else {
                // point
                lightDir = normalize(lightpos[i] - worldspacepos);
                float dist = distance(worldspacepos, lightpos[i]);
                attenuation = min(1.0, 1.0 / (function[i][0] + dist * function[i][1] + pow(dist, 2) * function[i][2]));
                if (type[i] == 2.0) {
                    // spot
                    vec4 currDir = normalize(worldspacepos - lightpos[i]);
                    vec4 spotDir = normalize(lightdir[i]);
                    float x = acos(dot(currDir, spotDir));
                    float inangle = innerangle[i];
                    float outangle = outerangle[i];

                    if (x <= inangle) {
                        intensity = lightcolor[i];
                    } else if (x > inangle && x <= outangle) {
                        float falloff =  -2.0 * pow(((x-inangle) / (outangle - inangle)), 3) + 3.f * pow(((x-inangle) / (outangle - inangle)), 2);
                        intensity = lightcolor[i] * (1-falloff);
                    } else {
                        intensity = vec4(0,0,0,1);
                    }
                }
            }

            // diffuse light
            float dotprod1 = clamp(dot(lightDir, worldspacenorm), 0.0, 1.0);
            vec4 diffuse = attenuation * intensity * kd * cdiffuse * dotprod1;
            fragColor += diffuse;

            // specular light
            vec4 reflectedDir = reflect(-lightDir, worldspacenorm);
            vec4 directionToCamera = normalize(camerapos - worldspacepos);
            float dotprod2 = clamp(dot(directionToCamera, reflectedDir), 0.0, 1.0);
            float coeff = shininess;
            if (shininess == 0) {
                coeff = 1;
            }
            float closeness = pow(dotprod2, coeff);
            vec4 specular = attenuation * intensity * ks * cspecular * closeness;
            fragColor +=  specular;
        }
    }




}
