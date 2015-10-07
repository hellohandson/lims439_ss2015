uniform vec2 u_resolution;

vec4 drawRect () {
    vec4 temp = vec4(0.);
    return temp;
}

void main(){
    // pixel base border
    vec3 color = vec3(0.0);

    //boarder in pixelValues stored in vector 
    //x=left, y=bottom, z=right, w=top
    vec4 thickness = vec4(10.0, 20.0, 30.0, 50.0);
    //vec4 smoothness = vec4 (0.01, 0.03, 0.08, 0.02);
    vec4 smoothness = vec4(5., 1., 10., 20.);

    vec4 coors = vec4( gl_FragCoord.x, gl_FragCoord.y, u_resolution.x-gl_FragCoord.x, u_resolution.y-gl_FragCoord.y);

    vec4 lbrt = floor (coors / thickness);
    lbrt = smoothstep( thickness-smoothness, thickness , coors);
    
    color = vec3( lbrt.x* lbrt.y * lbrt.z* lbrt.w); 

    gl_FragColor = vec4(color, 1.0);
}