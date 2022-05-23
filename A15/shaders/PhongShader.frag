#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform sampler2D texSampler;

layout(binding = 2) uniform GlobalUniformBufferObject {
	vec3 lightDir;
	vec3 lightPos;
	vec3 lightColor;
	vec3 eyePos;
	vec4 coneInOutDecayExp;
	vec4 selector;
} gubo;




/**** Modify from here *****/

vec3 direct_light_dir(vec3 pos) {
	// Directional light direction
	return gubo.lightDir;
}

vec3 direct_light_color(vec3 pos) {
	// Directional light color
	return gubo.lightColor;
}

vec3 point_light_dir(vec3 pos) {
	// Point light direction
	vec3 lightDir = normalize(gubo.lightPos - pos);
	return lightDir;
}

vec3 point_light_color(vec3 pos) {
	// Point light color
	float g = gubo.coneInOutDecayExp.z;
	float beta = gubo.coneInOutDecayExp.w;

	vec3 lightDir = gubo.lightPos - pos;
	float base = g/length(lightDir);
	float decay = pow(base, beta);

	vec3 lightColor = decay * gubo.lightColor;
	return lightColor;
}

vec3 spot_light_dir(vec3 pos) {
	// Spot light direction
	vec3 lightDir = normalize(gubo.lightPos - pos);
	return lightDir;
}

vec3 spot_light_color(vec3 pos) {
	// Spot light color
	float g = gubo.coneInOutDecayExp.z;
	float beta = gubo.coneInOutDecayExp.w;

	vec3 lightDir = gubo.lightPos - pos;
	float base = g/length(lightDir);
	float decay = pow(base, beta);

	float c_out = gubo.coneInOutDecayExp.x;
	float c_in = gubo.coneInOutDecayExp.y;

	vec3 d = gubo.lightDir;
	float dim_effect = clamp((dot(normalize(lightDir), d) - c_out) / (c_in - c_out), 0 , 1);

	vec3 lightColor = gubo.lightColor * decay * dim_effect;
	return lightColor;
}

/**** To from here *****/





void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 EyeDir = normalize(gubo.eyePos.xyz - fragPos);
	
	vec3 lD;	// light direction from the light model
	vec3 lC;	// light color and intensity from the light model
	
	lD = direct_light_dir(fragPos) * gubo.selector.x +
	     point_light_dir(fragPos)  * gubo.selector.y +
	     spot_light_dir(fragPos)   * gubo.selector.z;
	lC = direct_light_color(fragPos) * gubo.selector.x +
	     point_light_color(fragPos)  * gubo.selector.y +
	     spot_light_color(fragPos)   * gubo.selector.z;

	vec3 Diffuse = (texture(texSampler, fragTexCoord).rgb * gubo.selector.w + vec3(1,1,1) * (1-gubo.selector.w)) * (max(dot(Norm, lD),0.0f) );
	vec3 Specular = vec3(pow(max(dot(EyeDir, -reflect(lD, Norm)),0.0f), 64.0f));
	
	outColor = vec4((Diffuse + Specular) * lC, 1.0f);	
}