// vertex shader
 
#version 150
 
uniform mat4 modelViewProjectionMatrix;
in vec4 position;
uniform vec2 u_mouse;
uniform vec2 u_resolution;
uniform vec2 u_circleDimension;
uniform int u_pointCount;

uniform samplerBuffer tex;
 
void main(){
	vec4 pos = position ;
    pos.xy += u_mouse;
    // direction vector from mouse position to vertex position.
    vec2 dir = pos.xy - u_mouse;

 
    // distance between the mouse position and vertex position.
    //float dist =  distance(pos.xy, u_mouse);
 
        // pos.x += u_mouse.x;// + u_circleDimension.x ;
        // pos.y += u_mouse.y; //+ u_circleDimension.y ;
        // pos.y += dir.y;


    gl_Position = modelViewProjectionMatrix * pos;
    // gl_Position = modelViewProjectionMatrix * pos;
}