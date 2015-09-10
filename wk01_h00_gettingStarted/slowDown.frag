#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;

void main() {
    float s_time = u_time/8.;
 gl_FragColor = vec4(abs(sin(s_time)),abs(cos(s_time)),0.0,1.0);
}