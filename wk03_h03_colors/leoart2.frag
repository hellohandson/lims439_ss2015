#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;
vec3 colorA = vec3(255., 255., 255.)/256.;
vec3 colorB = vec3(10., 10., 255.)/256.;
vec3 colorC = vec3(125.,10.,0.)/256.;

float grad (float _y, float _time) {
    float _x = abs( ((sin( (_y - -0.049) / 0.122 ) * 0.575 + sin( (_y - _time) / 0.877 ) * 0.607 + -0.063) - 0.117) / 0.787 ) * 0.648;
    return _x;
}

float drawLeftRightBorder (vec2 st, vec4 rect) {
    
    float tx = smoothstep (rect.x, rect.x-.2, st.x) + smoothstep (rect.z, rect.z+.2, st.x);
    return tx;
}

void main() {
    float t = mod(u_time, 100.) /10.;
    vec2 st = gl_FragCoord.xy/u_resolution;
    
    vec4 rect = vec4(0.2, 0.2, 0.8, 0.8);
    float rectMod = drawLeftRightBorder(st, rect);
    
    float colorMod = grad (st.y, t);
    vec3 priColor = vec3(colorB.r, colorB.g, colorA.b* colorMod);
    vec3 finalColor = mix(colorA, colorB, colorMod);
    finalColor = mix (finalColor, colorC, smoothstep(0.5,1., colorMod) );
    
    finalColor = mix (finalColor, colorA, rectMod );
    
    gl_FragColor = vec4(finalColor ,1.0);
}

