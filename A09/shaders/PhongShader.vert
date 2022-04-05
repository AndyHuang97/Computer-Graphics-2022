#version 450
#extension GL_ARB_separate_shader_objects : enable

	mat4 mvpMat;
	mat4 mMat;
	mat4 nMat;
} ubo;


layout(location = 0) out vec3 fragPos;

	gl_Position = ubo.mvpMat * vec4(inPosition, 1.0);
	fragPos = (ubo.mMat * vec4(inPosition, 1.0)).xyz;
}