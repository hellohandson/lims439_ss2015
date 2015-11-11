#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.14159265359
#define TWO_PI 6.28318530718

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;
float drawPoly (vec2 st, vec2 center ,float sides) {
    if (sides <= 1.) {
        return 0.;
    }
     float N = sides;
     st -= 0.5;

     //st -= center;
        // st= st+center;
        // Angle and radius from the current pixel
        float a = atan(st.x,st.y)+PI;
        float r = TWO_PI/float(N);
        float d = 0.0;
        // Shaping function that modulate the distance
        d = cos(floor(.5+a/r)*r-a)*length(st);
         //(smoothstep(size- thickness -.005, size-thickness, d) - smoothstep(size, size +.005, d)  ) 
        return  (smoothstep( .15, 0.2, d) - smoothstep(0.2, 0.25, d)  ) ;
        //return (1.0-smoothstep(.4,.41,d));
}
float drawPolyOutline (vec2 pixel, vec2 center, float size, int sides, float thickness) {
  // pixel /= u_resolution.xy;
  // center /= u_resolution.xy;
  pixel -= center;  
  // pixel.x *= u_resolution.x/u_resolution.y;
  // size /= u_resolution.y;
  // thickness /= u_resolution.y;
    // Angle and radius from the current pixel
  vec2 pos = pixel ;
  float a = atan(pos.x,pos.y)+PI ;
  float r = TWO_PI/float( sides) ;
  
  // Shaping function that modulate the distance
  float d = cos(floor(.8 +  a/r) * r - a ) * length(pixel );
  return (smoothstep(size- thickness -.005, size-thickness, d) - smoothstep(size, size +.005, d)  )  ;
}

float random (in float x) {
    return fract(sin(x)*1e4);
}

float random (in vec2 st) { 
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))* 
        43758.5453123);
}
float random2 (in vec2 st) { 
    return fract(sin(dot(st.xy,
                         vec2(12.9898,178.233)))* 
        63758.5453123);
}
void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    float mousePosModifier = u_mouse.x / u_resolution.x;
    float numberOfRows = 70.;

    vec2 columnsRows = vec2 (20., 20.);
    st *= columnsRows; 

    vec2 ipos = floor(st);  // get the integer coords
    vec2 fpos = fract(st);  // fraction coords

    float displacement = floor(u_time*20. * random(ipos.y)) ;

    vec3 color = vec3(1.);

    ipos.x = floor (ipos.x - displacement);
    ipos.y = 0.;
    //
    //vec3 color = vec3(char(fpos,100.*pct));
    float sides = random( ipos );
    sides = floor (sides * 6. + 2.);
    float pct = random(ipos);
    float pct2 = random2(ipos);
    color = vec3( drawPoly( fpos, ipos, sides   ) ); 

    color = mix(color,vec3(color.r,0.,0.), step(.7,pct));
    color = mix(color,vec3(0.,color.g,0.), step(.8,pct2));


    gl_FragColor = vec4(color,1.0);
}