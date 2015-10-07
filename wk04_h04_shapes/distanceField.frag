#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

//shaping function from wk 2 assignment
float plot2( float pct){
     float t = (abs( sin( (pct +0.666) / 0.125 ) * 0.449 / 1.144 ) * 0.647 * 0.921 + ((fract( pct ) * 0.845)));
    return t;
}

float drawCirclePixel (vec2 pixel, vec2 center, float radius) {
	float dist = length(center - pixel)  ;
	dist = smoothstep (1.,0.97, dist / (radius));
	return dist;
}

void main(){
	vec3 color1 = vec3(1., 0.3, 0.5);
	vec3 color2 = vec3(0., 0.3, 1.);

	float pulse = sin(u_time);
	float pulse2 = plot2(u_time/ 10.);
	
    float circ1 = drawCirclePixel(gl_FragCoord.xy , vec2 (80.,60.) , 60. - (30.*pulse) );

    float circ2 = drawCirclePixel(gl_FragCoord.xy , vec2 (u_mouse.xy) , 40. + (80.* pulse2));

    vec3 color = vec3(circ1)*color1 + vec3(circ2)* color2;

	gl_FragColor = vec4( color, 1.0 );
}