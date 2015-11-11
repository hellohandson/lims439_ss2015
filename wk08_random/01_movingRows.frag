#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

float random (vec2 st) { 
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))* 
        43758.5453123);
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    
    float displacement = sin(fract(u_time/8.)) * u_time*10.;
    float numberOfRows = 20.;

    st *= vec2(100. , numberOfRows); 

    if (mod(st.y,2.) < 1.) {
        displacement *= -1.;
    }
    
    st.x += displacement;
    vec2 ipos = floor(st);  // get the integer coords

    
    //ipos.y *=   u_time/30.;
 
    vec3 color = vec3(random( ipos )); 
    color = step(0.4,color);


    gl_FragColor = vec4(color,1.0);
}