#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

float random (in float x) {
    return fract(sin(x)*1e7);
}
float random (in vec2 st) { 
    return fract(
                sin(
                    dot(st.xy, vec2(23.123123 , 1234.23123))
                    )
                * 232.5453123);
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    float mousePosModifier = u_mouse.x / u_resolution.x;
    float numberOfRows = 50.;

    vec2 columnsRows = vec2 (70., 50.);
    st *= columnsRows; 

    vec2 ipos = floor(st);  // get the integer coords
    vec2 fpos = fract(st);  // fraction coords

    vec2 displacement = vec2(u_time*1.) * sin(u_time/10.) ; 
    displacement *= vec2(-1.,0.0) * random(1.0+ipos.y);

    vec3 color = vec3(1.);
    
    //duplicate interger coords to displace differently to apply to single color
    vec2 offsetPos = ipos ;
    offsetPos.x = floor (offsetPos.x + displacement.x + 0.1);

    // add displacement to integer coords of X
    ipos.x = floor (ipos.x + displacement.x);

    color *= vec3( random( offsetPos ) , random( ipos ) , random( ipos ) ); 
    // convert random grayscale boxes to b&w based on threshold modified by mouse.x position
    color = step(0.6 + mousePosModifier * 0.4, color);

    color *= 1. - step(0.3,fract(st.y)) ;
    gl_FragColor = vec4(color,1.0);
}