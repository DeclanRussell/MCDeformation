#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec3 vertexColor;
//layout (location = 2) in vec2 texCoord;

out vec3 position;
smooth out vec3 normal;
smooth out vec3 color;
//out vec2 TexCoords;

uniform mat4 MV;
uniform mat3 normalMatrix;
uniform mat4 MVP;


void main(){
   //TexCoords = texCoord;
   color = vertexColor;
   normal = normalize(normalMatrix * vertexNormal);
   position = vec3(MV * vec4(vertexPosition,1.0));
   gl_Position = MVP * vec4(vertexPosition,1.0);
}
