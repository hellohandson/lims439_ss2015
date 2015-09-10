#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution; 
uniform vec2 u_mouse; 
uniform float u_time;


vec3 randomSpeed (vec3 t) {
    t.r = fract(sin(dot(t.r ,12.9898)));
    t.g = fract(sin(dot(t.g ,12.9898)) );
    t.b = fract(sin(dot(t.b ,12.9898)));
    return t;
}

void main(){
    vec3 new = vec3(u_time/12.);
    new.r *= 3.;
    new.g *= 2.5;
    new.b *= 2.;
    vec3 new2 = randomSpeed(new);
    
 gl_FragColor = vec4(new2, 1.0);
}