#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;

uniform float u_time;

vec3 c1 = vec3(1.0, 0.0, 0.0);
vec3 c2 = vec3(1.0, 0.5, 0.0);
vec3 c3 = vec3(1.0, 1.0, 0.0);
vec3 c4 = vec3(0.0, 0.5, 0.0);
vec3 c5 = vec3(0.0, 0.0, 1.0);
vec3 c6 = vec3(0.5, 0.0, 0.5);


vec3 rainbow(float x, float t)
{    
    vec3 c = vec3(1.);
    float _step = 1./6.;
    c = mix( c, c1, smoothstep(0.- t*.1, 0.+ 0.1+ t*.1, x));
    c = mix( c, c2, smoothstep(_step- t*.1, _step+ 0.1+ t*.1, x));
    c = mix( c, c3, smoothstep(_step*2.- t*.1, _step*2.+ 0.1+ t*.1, x));
    c = mix( c, c4, smoothstep(_step*3.- t*.1, _step*3.+ 0.1+ t*.1, x));
    c = mix( c, c5, smoothstep(_step*4.- t*.1, _step*4.+ 0.1+ t*.1, x));
    c = mix( c, c6, smoothstep(_step*5.- t*.1 , _step*5.+ 0.1+ t*.1, x));
    return c;
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    float t = abs (sin(u_time));
    vec3 color = rainbow(st.y, t);

    gl_FragColor = vec4(color,1.0);
}

