#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_mouse;
uniform vec2 u_resolution;

float noise(vec2 pos) {
  return abs(fract(sin(dot(pos,vec2(20.9*u_time,28.633*u_mouse.x))) * 4378.5453*u_time));
}

void main( void ) {


  gl_FragColor += noise( gl_FragCoord.xy / u_resolution.xy );
}