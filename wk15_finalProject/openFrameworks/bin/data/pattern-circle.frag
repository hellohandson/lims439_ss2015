//pattern for circle

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

void main( void ) {
    vec4 tempColor = vec4(0.);
    float colorF = 0.;
    for(int i=0;i< u_pointCount; ++i)
    { 
      int x = i*4;
      mat4 matrix = mat4( 
          texelFetch(tex, x),
          texelFetch(tex, x+1),
          texelFetch(tex, x+2), 
          texelFetch(tex, x+3)
      );
      
		  vec2 pos = vec2(matrix[0][0], matrix[0][1]);
		  pos.y = u_resolution.y - pos.y;
		  vec2 _pos = ((gl_FragCoord.xy - pos) / u_resolution.xy) * vec2(u_resolution.x/u_resolution.y, 1.);
    	float f = 0.0;

      float distanceFieldModifier = abs(length(_pos) - u_circleDimension.x/u_resolution.y );
      f =  0.03 + .03/10./ distanceFieldModifier;
      // f = (distanceFieldModifier > 0.2) ? f/ (20.* (distanceFieldModifier-0.2 )) : f; //tree rings
      f = (distanceFieldModifier > 0.2) ? f/(20.* (distanceFieldModifier)) : f;
    	
    	tempColor += mix (tempColor, vec4( vec3(1.0,1.0,5.0) * f,  f ), 1.);
    }
    outputColor = vec4(tempColor);
}