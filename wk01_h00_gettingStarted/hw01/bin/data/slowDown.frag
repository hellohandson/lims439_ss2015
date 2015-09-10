#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution; 
uniform vec2 u_mouse;
uniform float u_time; 

float speed = 12.0;
float seed = 13.344534;

vec3 randomSpeed (vec3 t) {
    t.r = fract(sin(dot(t.r ,seed)));
    t.g = fract(sin(dot(t.g ,seed)) );
    t.b = fract(sin(dot(t.b ,seed)));
    return t;
}

void main(){
    vec3 new = vec3(u_time/speed);
    new.r *= 3.;
    new.g *= 2.5;
    new.b *= 2.;
    vec3 new2 = randomSpeed(new);
    
 gl_FragColor = vec4(new2, 1.0);
}