//pattern for metaball

#version 150
#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_mouse;
uniform vec2 u_resolution;
uniform float circ_opacity;
uniform vec2 u_circleDimension;
out vec4 outputColor;

uniform int u_pointCount;
uniform samplerBuffer tex;

float u_circles[200];

float metaball(vec2 uv , vec2 center , float size)
{
  return size/length(uv - center);
}

void main( void ) {
    vec4 tempColor = vec4(0.);
    float colorF = 0.;
    vec2 uv = gl_FragCoord.xy / u_resolution.xy;
    uv.y *= u_resolution.y / u_resolution.x;
    for(int i=0;i< u_pointCount; ++i)
    { 
      int x = i*4;
      mat4 matrix = mat4( 
          texelFetch(tex, x),
          texelFetch(tex, x+1),
          texelFetch(tex, x+2), 
          texelFetch(tex, x+3)
      );
      
      vec2 size = u_circleDimension;
      vec2 pos = vec2(matrix[0][0], matrix[0][1]);
      pos.y = u_resolution.y - pos.y;
      vec2 _pos = ( (gl_FragCoord.xy - pos) / u_resolution.xy) * vec2(u_resolution.x/u_resolution.y, 1.);
      _pos = pos / u_resolution.x;
      colorF += metaball(uv , _pos, size.x/u_resolution.y);
      
    }

    float w = pow(colorF/4.0, 27.0); 
    vec3 c = vec3(w, w, w * 5.) * (1.3 - w/.6) * 3.;
    outputColor = vec4(c, c.r);
}