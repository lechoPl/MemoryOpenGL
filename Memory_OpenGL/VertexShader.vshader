#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

uniform vec2 position;
uniform float scale;
uniform float animationX;

void main(){	

	gl_Position.x = vertexPosition_modelspace.x * scale * animationX + position.x;
	gl_Position.y = vertexPosition_modelspace.y * scale + position.y;
	gl_Position.z = vertexPosition_modelspace.z;
    gl_Position.w = 1.0;
}
