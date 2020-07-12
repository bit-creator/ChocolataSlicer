#version 150

uniform mat4	ciModelViewProjection;
uniform mat3	ciNormalMatrix;


in vec4		ciPosition;
in vec3		ciNormal;

out highp vec3	Normal;

void main(void ) {
	gl_Position	= ciModelViewProjection * ciPosition;

	Normal = ciNormalMatrix * ciNormal;

}
