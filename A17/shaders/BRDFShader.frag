#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(binding = 2) uniform GlobalUniformBufferObject {
	// Direct lights parameters (for diffuse and specular)
	vec3 lightDir0;
	vec3 lightColor0;
	vec3 lightDir1;
	vec3 lightColor1;
	vec3 lightDir2;
	vec3 lightColor2;
	vec3 lightDir3;
	vec3 lightColor3;

	// Ambient light parameters
	vec3 AmbColor;	// also Bottom color for Hemispheric light,
					//      Constant term for Spherical Harmonics light
	vec3 TopColor;	// also DyColor for Spherical Harmonics light
	vec3 DzColor;
	vec3 DxColor;
	
	// Other parameters (not relevant for the exercise)
	vec3 eyePos;
	vec4 selector;
} gubo;

/**** Modify from here *****/

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;


vec3 Case1_Color(vec3 N, vec3 V, vec3 Cd, vec3 Ca, float sigma) {
	// Oren Nayar Diffuse + Ambient
	// No Specular
	// One directional light (lightDir0 and lightColor0)
	//
	// Parameters are:
	//
	// vec3 N : normal vector
	// vec3 V : view direction
	// vec3 Cd : main color (diffuse color)
	// vec3 Ca : ambient color
	// float sigma : roughness of the material

	vec3 L = gubo.lightDir0;
	float theta_i = acos(dot(L, N));
	float theta_j = acos(dot(V, N));
	float alpha = max(theta_i, theta_j);
	float beta = min(theta_i, theta_j);
	float A = 1 - 0.5 * pow(sigma,2) / (pow(sigma,2) + 0.33);
	float B = 0.45 * pow(sigma,2) / (pow(sigma,2) + 0.09);
	vec3 v_i = normalize(L - dot(L,N)*N);
	vec3 v_j = normalize(V - dot(V,N)*N);
	float G = max(0, dot(v_i, v_j));
	vec3 l = Cd * clamp(dot(L,N), 0, 1);
	vec3 BRDF = l*(A + B*G*sin(alpha)*tan(beta));

	vec3 la = gubo.AmbColor;
	return BRDF + la * Ca;
}

vec3 Case2_Color(vec3 N, vec3 V, vec3 Cd, vec3 Ca) {
	// Lambert Diffuse + Hemispheric
	// No Specular
	// One directional light (lightDir0 and lightColor0)
	// Hemispheric light oriented along the y-axis
	//
	// Parameters are:
	//
	// vec3 N : normal vector
	// vec3 V : view direction
	// vec3 Cd : main color (diffuse color)
	// vec3 Ca : ambient color

	vec3 L = gubo.lightDir0;
	vec3 BRDF = Cd * vec3(clamp(dot(L, N), 0, 1));
	vec3 HemiDir = vec3(0.0f, 1.0f, 0.0f);
	
	vec3 la =  (dot(N,HemiDir)+1)/2 * gubo.TopColor + (1-dot(N,HemiDir))/2 * gubo.AmbColor;
	
	return BRDF + la * Ca;
}

vec3 Case3_Color(vec3 N, vec3 V, vec3 Cs, vec3 Ca, float gamma)  {
	// Spherical Harmonics
	// Blinn Specular
	// Four directional lights (lightDir0 to lightDir3, and lightColor0 to lightColor3)
	//
	// Parameters are:
	//
	// vec3 N : normal vector
	// vec3 V : view direction
	// vec3 Cs : specular color
	// vec3 Ca : ambient color
	// float gamma : Blinn exponent

	vec3 h_lx;
	vec3 BRDF = vec3(0,0,0);
	float base;

	// light0
	h_lx = normalize(gubo.lightDir0 + V);
	base = clamp(dot(N, h_lx), 0, 1);
	BRDF += Cs * pow(base, gamma); 
	
	// light1
	h_lx = normalize(gubo.lightDir1 + V);
	base = clamp(dot(N, h_lx), 0, 1);
	BRDF += Cs * pow(base, gamma); 

	// light2
	h_lx = normalize(gubo.lightDir2 + V);
	base = clamp(dot(N, h_lx), 0, 1);
	BRDF += Cs * pow(base, gamma); 

	// light3
	h_lx = normalize(gubo.lightDir3 + V);
	base = clamp(dot(N, h_lx), 0, 1);
	BRDF += Cs * pow(base, gamma); 
	
	vec3 la = gubo.AmbColor + N.x * gubo.DxColor + N.y * gubo.TopColor + N.z * gubo.DzColor;

	return BRDF + la * Ca;
}



/**** To here *****/




void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 EyeDir = normalize(gubo.eyePos.xyz - fragPos);
	
	float AmbFact = 0.025;
	
	vec3 DifCol = texture(texSampler, fragTexCoord).rgb * gubo.selector.w +
				  vec3(1,1,1) * (1-gubo.selector.w);

	vec3 CompColor = gubo.selector.x *
						Case1_Color(Norm, EyeDir, DifCol, DifCol, 1.2f) +
					 gubo.selector.y *
						Case2_Color(Norm, EyeDir, DifCol, DifCol) +
					 gubo.selector.z *
						Case3_Color(Norm, EyeDir, vec3(1.0f,1.0f,1.0f), DifCol, 200.0f);
	
	outColor = vec4(CompColor, 1.0f);	
}