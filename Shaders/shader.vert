#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;
//layout (location = 3) in vec3 aTangent;
//layout (location = 4) in vec3 aBitangent;  

out vec4 vCol;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec4 DirectionalLightSpacePos;
//out mat3 mat3 TBN;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 inverseTransposeModel;
uniform mat4 directionalLightTransform; 

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	//vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
	vCol = vec4(1.0f, 1.0f, 1.0f, 1.0f); // white
	
	DirectionalLightSpacePos = directionalLightTransform * model * vec4(pos, 1.0);
	
	TexCoord = tex;
	
	Normal = mat3(inverseTransposeModel) * norm;
	
	FragPos = vec3(model * vec4(pos, 1.0)); 
	
   //vec3 T = normalize(vec3(model * vec4(aTangent, 0.0)));
   //vec3 B = normalize(vec3(model * vec4(aBitangent, 0.0)));
   //vec3 N = normalize(vec3(model * vec4(aNormal, 0.0)));
   
   //mat3 TBN = transpose(mat3(T, B, N));
	
}