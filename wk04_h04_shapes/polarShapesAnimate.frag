#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

void main(){
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec3 color = vec3(0.0);

    vec2 pos = vec2(0.5)-st;

    float r = length(pos)*2.;
    float a = atan(pos.y,pos.x)  ;

    float noOfPoints = 5.+ fract(abs( sin(u_time))) * 10. ;

    float f = smoothstep(-.5,1., cos(a* noOfPoints ))*0.1+0.5;

    color = vec3( 1.-smoothstep(f,f+0.02, r) );
    color -= vec3( 1.-smoothstep(f,f+0.01, r +0.2) );

    gl_FragColor = vec4(color, 1.0);
}