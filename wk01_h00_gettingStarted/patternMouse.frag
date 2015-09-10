#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution; 
uniform vec2 u_mouse; 
uniform float u_time; 

float speed = 50.0;
float seed = 13.344534;
float cirSizeRatio = .2;

vec3 randomSpeed (vec3 t) {
    t.r = fract(sin(dot(t.r ,seed)));
    t.g = fract(sin(dot(t.g ,seed)));
    t.b = fract(sin(dot(t.b ,seed)));
    return t;
}

void main(){
    vec3 new = vec3(u_time/speed);
    new.r *= 3.;
    new.g *= 2.5;
    new.b *= 2.;
    vec3 new2 = randomSpeed(new);
    
    vec2 p = gl_FragCoord.xy/u_resolution;
    vec2 m = u_mouse/u_resolution;

    float dist_to_mouse = distance(p,m)  ;
    
    vec3 finalC = (dist_to_mouse < cirSizeRatio )? 
        vec3(m, new2.gb) : vec3(0,0,0);
 gl_FragColor = vec4(finalC, 1.0);
}