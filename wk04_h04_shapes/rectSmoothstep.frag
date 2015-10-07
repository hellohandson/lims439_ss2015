uniform vec2 u_resolution;

void main(){
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec3 color = vec3(0.0);

    //boarder percentages stored in vector 
    //x=left, y=bottom, z=right, w=top
    vec4 thickness = vec4(0.1,0.2, 0.1, 0.1);
    vec4 smoothness = vec4 (0.01, 0.03, 0.08, 0.02);

    vec4 coors = vec4( st.x, st.y, 1.0-st.x, 1.0-st.y);

    vec4 lbrt = step (thickness, coors);
    lbrt = smoothstep( thickness-smoothness, thickness , coors);
    // lbrt = floor (coors);
    // The multiplication of left*bottom will be similar to the logical AND.
    color = vec3( lbrt.x* lbrt.y * lbrt.z* lbrt.w); 

    gl_FragColor = vec4(color, 1.0);
}