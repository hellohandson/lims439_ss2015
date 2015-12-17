//intersection for circle effect

#version 150

#ifdef GL_ES
precision mediump float;
#endif
in vec4 color;
out vec4 outColor;

#define PI 3.14159265359
#define TWO_PI 6.28318530718
#define circleEdge 64.

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;
uniform vec2 u_circleDimension;
uniform int u_pointCount;

uniform samplerBuffer tex;
uniform sampler2DRect tex1;

vec2 imgSize = vec2(1108., 506.);

float drawPoly (vec2 st, vec2 center , vec2 size, float sides) {

     float N = sides;
     //st = st * 2. - 1.;
     st -= center;
     //fix aspect ratio so that regardless of screen dimensions the circle is round
     st.y *= size.x/size.y;
        float a = atan(st.x,st.y)+PI;
        float r = TWO_PI/float(N);
        float d = 0.0;
        
        d = cos(floor(.5+a/r)*r-a)*length(st);
        float alias = size.x / 40.;
        return 1. - smoothstep(size.x-alias, size.x, d);
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    //size is in 90pixels
    vec2 size = u_circleDimension  ;
    //normalise sizing;
    size /=  u_resolution.xy ;
    vec3 color = vec3( 0. );


    float colorF = 0.;

    float u_circles[200];
    for(int i=0;i< u_pointCount; ++i)
    { 
      int x = i*4;
      mat4 matrix = mat4( 
          texelFetch(tex, x),
          texelFetch(tex, x+1),
          texelFetch(tex, x+2), 
          texelFetch(tex, x+3)
      );
      vec2 goPosition = vec2(matrix[0][0], matrix[0][1])/u_resolution.xy;
      goPosition.y = 1.0 - goPosition.y;
      u_circles[i] = drawPoly( st, goPosition, size, circleEdge);
      
    }
    for(int i=0;i< u_pointCount; ++i)
    { 
      float tempColor = 0.;
      for (int j=i+1; j < u_pointCount; j++ ) {
        tempColor += u_circles[i] * u_circles[j];
      }
      colorF +=  tempColor ;
    }
    colorF = clamp(colorF , 0.0,1.0);

    vec2 pos = gl_FragCoord.xy;
    pos.y = u_resolution.y- pos.y;
    pos = pos.xy * (imgSize.xy / u_resolution.xy);
    vec4 gTxt = texture(tex1, pos)  ;

    outColor = gTxt * colorF;

}
