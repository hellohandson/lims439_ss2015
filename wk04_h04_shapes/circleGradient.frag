
#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

void main(){
	vec2 st = gl_FragCoord.xy/u_resolution;
    float pct = 0.0;

    // a. The DISTANCE from the pixel to the center
    pct = distance(st, vec2(0.5)) ;
    

    // b. The LENGTH of the vector 
    //    from the pixel to the center 
    vec2 toCenter = vec2(0.5)-st ;
    // pct = length(toCenter );
     // pct = length(toCenter )* 2.;

    // c. The SQUARE ROOT of the vector 
    //    from the pixel to the center 
     vec2 tC = vec2(0.5)-st;
     //pct = sqrt(tC.x*tC.x+tC.y*tC.y) ;


    // fit the circle by multiplying results by 2 as it ranges from 0.5-0-0.5
    // pct *=  2. ;
    // fit the gradient using smoothstep to interpolate the distance to 0-1;
    // though the same, the outcome looks slightly different
    pct = smoothstep(0., .5, pct);

    vec3 color = vec3(pct);

	gl_FragColor = vec4( color, 1.0 );
}