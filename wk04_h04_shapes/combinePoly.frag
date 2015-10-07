#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.14159265359
#define TWO_PI 6.28318530718

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

// Reference to
// http://thndl.com/square-shaped-shaders.html

float drawRectAbs (vec2 pixel, vec2 center, vec2 size) {
  //vec2 t = vec2 (size.x , size.y);
  vec2 r = abs( pixel.xy - center.xy - size.xy / 2. );
  float sX = step(size.x/2., r.x );
  float sY = step(size.y/2., r.y );
  float s =  max( sX, sY ) ;
  return s;
}
float drawRectOutlineAbs (vec2 pixel, vec2 center, vec2 size) {
  //vec2 t = vec2 (size.x , size.y);
  vec2 r = abs( pixel.xy - center.xy - size.xy / 2. );
  float sX = step(size.x/2., r.x );
  float sY = step(size.y/2., r.y );
  float s =  max( sX, sY ) ;
  // s = step(.4, s) * step( s, .3);
  return s;
}

void main(){
  vec2 st = gl_FragCoord.xy/u_resolution.xy;
  st.x *= u_resolution.x/u_resolution.y;
  vec3 color = vec3(0.0);
  float d = 0.0;

  // Remap the space to -1. to 1.
  st = st *2.-1.;

  // Number of sides of your shape
  int N = 6;

  // Angle and radius from the current pixel
  float a = atan(st.x,st.y)+PI;
  float r = TWO_PI/float(N);
  
  // Shaping function that modulate the distance
  d = cos(floor(.5+a/r)*r-a)*length(st);

  
  //f=vec4(vec3(s),1.)

  color = vec3(1.0- drawRectAbs ( gl_FragCoord.xy, vec2 (50., 50.), vec2(100.,50.) ) );
  color = vec3(1.0- drawRectOutlineAbs ( gl_FragCoord.xy, vec2 (50., 50.), vec2(100.,50.) ) );
  // color = vec3(d);

  gl_FragColor = vec4(color,1.0);
}