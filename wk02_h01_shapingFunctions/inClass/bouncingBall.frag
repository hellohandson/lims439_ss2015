#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;

float F(float x, float p, float w){
    return (smoothstep(p-w*.5,p,x) + smoothstep(p+w*.5,p,x))-1.0;
}

void main() {
	vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec3 color = vec3(0.);
 
 	vec2 p = vec2(cos(u_time*0.5),sin(u_time*.05))*.25+.5;   
    float pct = F(st.x,p.x,.1);
    pct *= F(st.y,p.y,.1);

    color = vec3(step(.5, pct));
    gl_FragColor = vec4(color,1.0);
}