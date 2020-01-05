// http://in2gpu.com/2014/06/23/toon-shading-effect-and-simple-contour-detection/

#version 330
out vec4 out_color;

uniform vec3 color;
uniform vec3 lightPosition;
uniform vec3 eyePosition;
uniform int materialShininess;
uniform float materialDiffuse;
uniform float materialSpecular;

in vec3 world_pos;
in vec3 world_normal;

const int levels = 5;
const float scaleFactor = 1.0 / levels;

void main(){
    vec3 col = vec3(1.0,1.0,1.0);
    vec3 colorDiffuse = vec3(1.0,1.0,1.0);

    vec3 L = normalize( lightPosition - world_pos);
    vec3 V = normalize( eyePosition - world_pos);

    float difuza = max(0, dot(L,world_normal));
    colorDiffuse = colorDiffuse * materialDiffuse* floor(difuza * levels) * scaleFactor;

    vec3 H = normalize(L + V);

    float speculara = 0;

    if( dot(L,world_normal) > 0.0)
    {
        speculara = float(materialSpecular * abs(pow( max(0, dot( H, world_normal)), materialShininess)));
    }

    float specMask = (pow(dot(H, world_normal), materialShininess) > 0.4) ? 1 : 0;
    float edgeMask = (dot(V, world_normal) >  0.2) ? 1 : 0;

    col = edgeMask * (color + colorDiffuse + speculara * specMask);

    out_color = vec4(col,1);
}