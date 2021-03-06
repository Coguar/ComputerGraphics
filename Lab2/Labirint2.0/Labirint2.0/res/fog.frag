//fog fragment shader 
//................!!!....................... 
//if you decided how to compute fog distance 
//and you want to use only one fog equation 
//you don't have to use those if statements 
//Here is a tutorial and I want to show 
//different possibilities 
//......................................... 
#version 330 
layout(location = 0) out vec4 out_color; 
uniform vec3 light_position; 
uniform vec3 eye_position; 
uniform sampler2D texture1; 
//0 linear; 1 exponential; 2 exponential square 
uniform int fogSelector; 
//0 plane based; 1 range based 
uniform int depthFog; 
//can pass them as uniforms 
const vec3 DiffuseLight = vec3(0.15, 0.05, 0.0); 
const vec3 RimColor = vec3(0.2, 0.2, 0.2); 
//from vertex shader 
in vec3 world_pos; 
in vec3 world_normal; 
in vec4 viewSpace; 
in vec2 texcoord; 
const vec3 fogColor = vec3(0.5, 0.5,0.5); 
const float FogDensity = 0.05; 
void main(){ 
vec3 tex1 = texture(texture1, texcoord).rgb; 
//get light an view directions 
vec3 L = normalize( light_position - world_pos); 
vec3 V = normalize( eye_position - world_pos); 
//diffuse lighting 
vec3 diffuse = DiffuseLight * max(0, dot(L,world_normal)); 
//rim lighting 
float rim = 1 - max(dot(V, world_normal), 0.0); 
rim = smoothstep(0.6, 1.0, rim); 
vec3 finalRim = RimColor * vec3(rim, rim, rim); 
//get all lights and texture 
vec3 lightColor = finalRim + diffuse + tex1; 
vec3 finalColor = vec3(0, 0, 0); 
//distance 
float dist = 0; 
float fogFactor = 0; 
//compute distance used in fog equations 
if(depthFog == 0)//select plane based vs range based 
{ 
//plane based 
dist = abs(viewSpace.z); 
//dist = (gl_FragCoord.z / gl_FragCoord.w); 
} 
else 
{ 
//range based 
dist = length(viewSpace); 
} 
if(fogSelector == 0)//linear fog 
{ 
// 20 - fog starts; 80 - fog ends 
fogFactor = (80 - dist)/(80 - 20); 
fogFactor = clamp( fogFactor, 0.0, 1.0 ); 
//if you inverse color in glsl mix function you have to 
//put 1.0 - fogFactor 
finalColor = mix(fogColor, lightColor, fogFactor); 
} 
else if( fogSelector == 1)// exponential fog 
{ 
fogFactor = 1.0 /exp(dist * FogDensity); 
fogFactor = clamp( fogFactor, 0.0, 1.0 ); 
// mix function fogColor?(1?fogFactor) + lightColor?fogFactor 
finalColor = mix(fogColor, lightColor, fogFactor); 
} 
else if( fogSelector == 2) 
{ 
fogFactor = 1.0 /exp( (dist * FogDensity)* (dist * FogDensity)); 
fogFactor = clamp( fogFactor, 0.0, 1.0 ); 
finalColor = mix(fogColor, lightColor, fogFactor); 
} 
//show fogFactor depth(gray levels) 
//fogFactor = 1 - fogFactor; 
//out_color = vec4( fogFactor, fogFactor, fogFactor,1.0 ); 
out_color = vec4(finalColor, 1); 
}

