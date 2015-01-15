#version 400

in vec3 position;
smooth in vec3 normal;
smooth in vec3 color;
//in vec2 TexCoords;

struct lightInfo{
   vec3 position;
   vec3 intensity;
};

uniform lightInfo light;

uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
uniform float shininess;
//uniform sampler2D tex;

out vec4 fragColour;

vec3 ads(){
   vec3 n = normalize(normal);
   vec3 s = normalize(light.position - position);
   vec3 v = normalize(-position);
   vec3 r = reflect(-s, n);
   vec3 h = normalize(v + s);
   return light.intensity * (Ka + Kd * max(dot(s,n),0.0)+ Ks * pow(max(dot(h, n), 0.0), shininess));
}

void  main(){
   fragColour = vec4(ads()*color,1.0);// * texture(tex, TexCoords);
}
