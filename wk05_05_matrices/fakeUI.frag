#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.14159265359
#define TWO_PI 6.28318530718

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

//move red hexagons, 1st xPos, 2nd yPos
#define MOV(a,b,c,d,t) (vec2(a*cos(t)+b*cos(0.1*(t)), c*sin(t)+d*cos(0.1*(t))))


float drawPoly (vec2 pixel, vec2 center, float size, int sides) {
  pixel /= u_resolution.xy;
  center /= u_resolution.xy;
  pixel -= center;  
  pixel.x *= u_resolution.x/u_resolution.y;
  size /= u_resolution.y;
  // Angle and radius from the current pixel
  vec2 pos = pixel ;
  float a = atan(pos.x,pos.y)+PI ; //set the angle
  float r = TWO_PI/float( sides) ; //set the radius
  
  // Shaping function that modulate the distance
  float d = cos(floor(.5 +  a/r) * r - a ) * length(pixel );

  return 1.0 - smoothstep(size, size +.005, d)   ;
}

float drawPolyOutline (vec2 pixel, vec2 center, float size, int sides, float thickness) {
  pixel /= u_resolution.xy;
  center /= u_resolution.xy;
  pixel -= center;  
  pixel.x *= u_resolution.x/u_resolution.y;
  size /= u_resolution.y;
  thickness /= u_resolution.y;
  // Angle and radius from the current pixel
  vec2 pos = pixel ;
  float a = atan(pos.x,pos.y)+PI ;
  float r = TWO_PI/float( sides) ;
  
  // Shaping function that modulate the distance
  float d = cos(floor(.5 +  a/r) * r - a ) * length(pixel );
  return (smoothstep(size- thickness -.005, size-thickness, d) - smoothstep(size, size +.005, d)  )  ;
}

float drawCirclePixel (vec2 pixel, vec2 center, float radius, float thickness) {
    thickness /= radius;
    float dist = length(center - pixel);
    dist = smoothstep (1.-thickness - 0.03 , 1.-thickness, dist / (radius)) - smoothstep (1., 1.03, dist / (radius));
    return dist;
}
float drawCircleRings (vec2 pixel, vec2 center, float radius, int count) {
  float spacing = 0.02;
  float dist = length(center - pixel);
  float antiAlias = 2./radius;
  float thickness = 1./float(count) -spacing;
  float t = 0.;
  for(int i=0;i<count;++i)
  {
    float myThickness = 0.008 * fract (abs ( sin(u_time*2. + float(i)/6. ) *  (cos(u_time/4.)) ) );
    
    float sI = max (thickness * float(i) , 0. ) + (spacing* float(i) );

    t += smoothstep ( sI - antiAlias, sI , dist / (radius)) - smoothstep ( sI+myThickness, sI+ myThickness + antiAlias, dist / (radius)) ;
  }
    return t;
}
vec2 movingLine(vec2 uv, vec2 center, float radius)
{
    //angle of the line
    float theta0 = 90.0 * u_time / 2.;
    vec2 d = uv - center;
    float r = sqrt( dot( d, d ) );
    if(r<radius){
        //compute the distance to the line theta=theta0
        vec2 p = radius*vec2(cos(theta0*PI/180.0),
                            -sin(theta0*PI/180.0));
        float l = length( d - p* clamp( dot(d,p)/dot(p,p), 0.0, 1.0) );
        d = normalize(d); 
        //compute gradient based on angle difference to theta0
        float theta = mod(180.0*atan(d.y,d.x)/PI+theta0,360.0);
        float gradient = clamp(1.0-theta/90.0,0.,1.0);
        vec2 t = vec2(  1.0-smoothstep(0., 2.0, l) ,  0.2 * gradient);
        return t;
    }
    else return vec2(0.0);
}
float crossHair (vec2 uv, vec2 center, float radius) {
  float theta0 = 90.0 * u_time / 2.;
  vec2 d = uv - center;
  float r = sqrt( dot( d, d ) );
  float a = 180.0 * (atan(d.x,d.y)+PI ) / PI + u_time * 10.;

  if (  mod (a, 90.) < 0.5 && r > radius  && r < radius +20. ) 
  {
    return 1.0;
  } 
  else return 0.0;
}
float crossHairFlicker (vec2 uv, vec2 center, float radius) {
  float theta0 = 90.0 * u_time / 2.;
  vec2 d = uv - center;
  float r = sqrt( dot( d, d ) );
  float a = 180.0 * (atan(d.x,d.y)+PI ) / PI * (u_time+100.) /9.;

  if (  mod (a, 90.) < 0.5 && r > radius  && r < radius +20. ) 
  {
    return 1.0;
  } 
  else return 0.0;

}


void main(){
  vec3 color1 = vec3 (.1, 0.2, 1.);
  vec3 color2 =  vec3(0.35,0.76,0.83);
  vec3 color3 =  vec3(0.9,0.16,0.03);

  vec3 uiC = vec3 (0.);
  uiC += vec3 (drawCircleRings (gl_FragCoord.xy, u_resolution.xy/2., 400., 5) * color1) * 0.5;  
  uiC += vec3 ( crossHair(gl_FragCoord.xy, u_resolution.xy/2., 160.) * color2 );
  uiC += vec3 ( crossHairFlicker(gl_FragCoord.xy, u_resolution.xy/2., 240.) * color2 );
  uiC += vec3 ( crossHairFlicker(gl_FragCoord.xy, u_resolution.xy/2., 300.) * color2 );
  vec2 translate = 130.0*MOV(1.3,1.0,1.0,1.4,3.0+0.1*u_time);
  vec3 dotty = vec3 (drawPoly (gl_FragCoord.xy, u_resolution.xy/2. + translate, 8., 6))  ;
  translate = 50.0*MOV(1.54,1.7,1.37,1.8,sin(0.1*u_time+7.0)+0.2*u_time);
  vec3 dotty2 = vec3 (drawPoly (gl_FragCoord.xy, u_resolution.xy/2. + translate, 8., 8))  ;
  vec2 line = movingLine(gl_FragCoord.xy, u_resolution.xy/2., 320.);
   uiC +=   line.x * color2 ;
   uiC +=   line.y * color3 * abs (cos(u_time)) ;

  uiC += color3 * abs (sin(u_time * 4.) * dotty );
  uiC += color3 * abs (cos (u_time* 8.) *dotty2);
  gl_FragColor = vec4(uiC, 1.);
}