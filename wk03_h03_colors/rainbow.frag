//Target Colors for each band of color based on X position:
//L  x   color
//0  0.0 vec4(1.0, 0.0, 0.0, 1.0);
//1  0.2 vec4(1.0, 0.5, 0.0, 1.0);
//2  0.4 vec4(1.0, 1.0, 0.0, 1.0);
//3  0.6 vec4(0.0, 0.5, 0.0, 1.0);
//4  0.8 vec4(0.0, 0.0, 1.0, 1.0);
//5  1.0 vec4(0.5, 0.0, 0.5, 1.0);



#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;

vec3 rainbow(float x)
{    
    float level = floor(x * 6.0);
    float r = float(level <= 2.0) + float(level > 4.0) * 0.5;
    float g = max(1.0 - abs(level - 2.0) * 0.5, 0.0);
    float b = (1.0 - (level - 4.0) * 0.5) * float(level >= 4.0);
    return vec3(r, g, b);
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec3 color = rainbow(st.x);

    gl_FragColor = vec4(color,1.0);
}
