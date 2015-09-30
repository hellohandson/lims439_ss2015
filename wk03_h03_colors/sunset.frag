#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;

vec3 colorA = vec3(0.249,0.2241,0.912);
vec3 colorB = vec3(1.000,0.833,0.224);
vec3 colorC = vec3(1.000,0.13,0.05);

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec3 color = vec3(0.0);

    color = mix(colorA, colorB, smoothstep(0.,0.5, st.y));
    color = mix (color, colorC, smoothstep(0.5,1.0, st.y) );

    gl_FragColor = vec4(color,1.0);
}