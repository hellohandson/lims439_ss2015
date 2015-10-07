uniform vec2 u_resolution;

vec4 drawRect (vec2 pixel, float x, float y, float width, float height) {
    vec4 thickness = vec4(x, u_resolution.y - y - height, u_resolution.x - x - width, y);
    vec4 coors = vec4( pixel.x, pixel.y, u_resolution.x-pixel.x, u_resolution.y-pixel.y);
    return floor (coors / thickness);
}
vec4 drawRectOutline (vec2 pixel, float x, float y, float width, float height, float line) {
    vec4 thickness = vec4(x , u_resolution.y - y - height , u_resolution.x - x - width , y) - line;
    // thickness = thickness - 1.;
    vec4 inner = thickness + line;
    vec4 coors = vec4( pixel.x, pixel.y, u_resolution.x-pixel.x, u_resolution.y-pixel.y);
    vec4 rext = step (inner, coors) - step (thickness, coors)   ;
   // rext -= vec4(1.) - step (inner, coors);
    return  rext;
}

void main(){
    // pixel base border
    vec3 color = vec3(0.0);

    vec4 rect = drawRect (gl_FragCoord.xy, 10.,10., 200., 50.);
    vec4 rect2 = drawRectOutline (gl_FragCoord.xy, 200.,100., 150., 50., 5.);

    color = vec3( rect.x* rect.y * rect.z* rect.w);
    color += vec3( rect2.x* rect2.y * rect2.z* rect2.w);

    gl_FragColor = vec4(color, 1.0);
}