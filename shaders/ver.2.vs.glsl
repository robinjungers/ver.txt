#version 330 core

// Input
layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoords;

// Uniform input
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;
uniform bool uCastsLight;

// Output
out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexCoords;

void main() {

	vec4 vertexPosition = vec4(aVertexPosition, 1);
	vec4 vertexNormal = vec4(aVertexNormal, 0);

	vPosition = vec3(uMVMatrix * vertexPosition);
	vNormal = vec3(uNormalMatrix * vertexNormal);
	vTexCoords = aVertexTexCoords;

	gl_Position = uMVPMatrix * vertexPosition;

}
