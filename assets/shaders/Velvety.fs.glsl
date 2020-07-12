#version 150

uniform vec3	ciCameraUp;
uniform vec3	ciEyePos;

in vec3		Normal;

out vec4 	oColor;


const float rimWidth = 0.1;
const vec3  rimColor = vec3(0.70588, 0.68235, 0.62745);
const vec3  baseColor = vec3(0.41176,0.20392,0.13725);


void main(void ) {
	vec3 normal = -normalize(Normal );

	vec3 tangent = cross(normal, -normalize(ciCameraUp) );
	float d = abs(dot(tangent, -normalize(ciEyePos - gl_FragCoord.xyz) ) );
	d = smoothstep(rimWidth, 1.0, d );

	oColor = vec4(mix(rimColor, baseColor, d), 1.0 );

}
