uniform vec2 u_resolution;

vec3 drawRect (vec2 pixel, float x, float y, float width, float height) {
    vec4 thickness = vec4(x,y, u_resolution.x - x - width,  u_resolution.y - y - height);
    vec4 coors = vec4( pixel.x, pixel.y, u_resolution.x-pixel.x, u_resolution.y-pixel.y);
    vec4 returnV = step ( thickness, coors ) ;
    returnV = clamp(returnV, 0., 1.);
    return vec3( returnV.x * returnV.y * returnV.z * returnV.w);
}
vec3 drawRectOutline (vec2 pixel, float x, float y, float width, float height, float line) {
    vec3 outer = drawRect (gl_FragCoord.xy, x, y, width, height);
    vec3 inner = drawRect (gl_FragCoord.xy, x + line, y + line, width -  line * 2., height -  line * 2.);
   // rext -= vec4(1.) - step (inner, coors);
    return outer - inner ;
}

void main(){
    // pixel base border
    vec3 color = vec3(1.0);

    vec3 rect = drawRect (gl_FragCoord.xy, 10., 90., 200., 50.);
    vec3 rect2 = drawRectOutline (gl_FragCoord.xy, 10.,10., 150., 50., 5.);

    vec3 tC = vec3(1., 0.3, 0.4);
    vec3 tC2 = vec3(0.,1.,0.3);

    color = (rect2) * tC2 + rect*tC;
   

    gl_FragColor = vec4(color, 1.0);
}