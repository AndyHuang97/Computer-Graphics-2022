#version 450

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 1) uniform GlobalUniformBufferObject {
	float time;
} gubo;

void main() {

	outColor = vec4(sin(gubo.time), 
					cos(gubo.time*6.28), 
					sin(gubo.time),
					1.0f);
}