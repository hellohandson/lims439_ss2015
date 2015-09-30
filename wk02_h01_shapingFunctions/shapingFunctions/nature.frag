#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.14159265359

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

// formula to emulate wind chime movement
float plot1 (vec2 st, float pct){
    float stretch = u_mouse.y / u_resolution.y;
    float t = abs( sin( st.x / (0.5 + stretch) ) * 0.27 / 0.89 ) * 0.78; 
    return smoothstep( t-0.01, t, pct) - smoothstep( t, t+0.01, pct);
}

// formula to emulate Swan head bobbing movement
float plot2(vec2 st, float pct){
     float t = (abs( sin( (st.x +0.666) / 0.125 ) * 0.449 / 1.144 ) * 0.647 * 0.921 + ((fract( st.x ) * 0.845)));
    return smoothstep( t-0.01, t, pct) - smoothstep( t, t+0.01, pct);
}

// formula to emulate ants random movement
// float plot3 (vec2 st, float pct) {
//     float t = (((fract( sin( floor(st.x ) / 0.23 ) * 900. )) * (((fract( st.x )) * (fract(st.x )) * ((fract( st.x ) - 1.) * (0. -2.) + 1.)))) + ((fract( sin( floor( (st.x - 1.) ) / 0.23 ) * 900. )) * (((fract( (st.x - 1.) )) * (fract( (st.x - 1.) )) * ((fract( (st.x - 1.) ) - 1.) * (0. -2.) + 1.)) * (0. -1.) + 1.))) * 0.67;
//     return smoothstep( t-0.01, t, pct) - smoothstep( t, t+0.01, pct);
// }


// formula to emulate ants random movement
float plot3 (vec2 st, float pct) {
    float t = ((floor( st.x / 0.63 ) * 0.21) * (sin( st.x / 1. ) * 0.81 * (sin( st.x )));
    return smoothstep( t-0.01, t, pct) - smoothstep( t, t+0.01, pct);
}



void main() {
    vec2 st = gl_FragCoord.xy/u_resolution;

    vec3 color = vec3(0.);
    st.x = st.x + u_time / 4.;
    
    //plot1 function for wind chime movement
    //float pct = plot1(st, st.y);
    //plot2 function for Swan movement
    //float pct = plot2(st, st.y+0.1);
    //plot3 function for ants movement
    float pct = plot3(st*4., st.y);

    color = pct * vec3(0.0,1.0,0.0);

    gl_FragColor = vec4(color,1.0);
}

