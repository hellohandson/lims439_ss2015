//intersection for metaball effect

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

vec2 imgSize = vec2(1024., 683.);

float metaball(vec2 uv , vec2 center , float size)
{
  return size/length(uv - center);
  
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    st.y *= u_resolution.y / u_resolution.x;
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
      vec2 goPosition = vec2(matrix[0][0], matrix[0][1]);
      goPosition.y = u_resolution.y - goPosition.y;
      vec2 _pos = ( (gl_FragCoord.xy - goPosition) / u_resolution.xy) * vec2(u_resolution.x/u_resolution.y, 1.);
      _pos = goPosition / u_resolution.x;
      // u_circles[i] = drawPoly( st, goPosition, size, circleEdge);
      u_circles[i] = 0.;
      u_circles[i] = metaball(st , _pos, u_circleDimension.x/u_resolution.y);
      
    }

    for(int i=0;i< u_pointCount; ++i)
    { 
      float tempColor = 0.;
      int x = i*4;
      mat4 matrix = mat4( 
          texelFetch(tex, x),
          texelFetch(tex, x+1),
          texelFetch(tex, x+2), 
          texelFetch(tex, x+3)
      );
      vec2 goPosition = vec2(matrix[0][0], matrix[0][1]);
      goPosition.y = u_resolution.y - goPosition.y;

      for (int j=i+1; j < u_pointCount; j++ ) {
        int jIndex = j*4;
        mat4 jMatrix = mat4( 
            texelFetch(tex, jIndex),
            texelFetch(tex, jIndex+1),
            texelFetch(tex, jIndex+2), 
            texelFetch(tex, jIndex+3)
        );
        vec2 jPosition = vec2(jMatrix[0][0], jMatrix[0][1]);
        jPosition.y = u_resolution.y - jPosition.y;

        if (length(goPosition - jPosition) < u_circleDimension.x * 2.) {
           colorF +=  u_circles[i] ;
           colorF +=  u_circles[j] ;
        }
      }
    }
    //colorF = clamp(colorF , 0.0,1.0);
    float w = pow(colorF/4.0, 27.0); 
    vec3 c = vec3(w, w, w * 5.) * (1.3 - w/.6) * 3.;
    float c2 = clamp(w, 0., 1.) ;

    vec2 pos = gl_FragCoord.xy;
    pos.y = u_resolution.y- pos.y;
    pos = pos.xy * (imgSize.xy / u_resolution.xy);
    vec4 gTxt = texture(tex1, pos)  ;
    //colorF -= 2.;
    outColor = clamp(gTxt * c2, 0., 1.) ;

}