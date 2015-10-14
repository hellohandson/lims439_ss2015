#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.14159265359

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

float box(in vec2 _st, in vec2 _size){
    _size = vec2(0.5) - _size*0.5;
    vec2 uv = smoothstep(_size,
                        _size+vec2(0.001),
                        _st);
    uv *= smoothstep(_size,
                    _size+vec2(0.001),
                    vec2(1.0)-_st);
    return uv.x*uv.y;
}

float cross(in vec2 _st, float _size){
    return  box(_st, vec2(_size,_size/4.)) + 
            box(_st, vec2(_size/4.,_size));
}


float plotMove1 (float _time) {
	float t = (abs( sin( (_time +0.666) / 0.125 ) * 0.449 / 1.144 ) * 0.647 * 0.921 + ((fract( _time ) * 0.845)));
    return t;
}
float plotMove2 (float _time) {
    float t = abs( sin( _time / (0.5 ) ) * 0.27 / 0.89 ) * 0.78;
    return t;
}
void main() {
    vec2 st = gl_FragCoord.xy/u_resolution;
    vec2 pos = st;

    vec3 color = vec3(0.);
    //st.x = st.x + u_time / 4.;
     float pct = 0.5 - plotMove1(u_time/4.);
     float pct2 =  plotMove2(u_time/4.);

    //color = pct * vec3(0.0,1.0,0.0);

    vec2 translate = vec2 ( pct, pct2);
    pos += translate;
    color += cross(pos, 0.2);

    gl_FragColor = vec4(color,1.0);
}

