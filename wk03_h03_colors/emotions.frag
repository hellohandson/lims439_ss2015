#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform float u_time;

// convert rgb 255,255,255 values to dec vec3 for easier picking of colors in photoshop
vec3 colorA = vec3(255., 13., 0.)/256.;
vec3 colorB = vec3(100,102.,250.)/256.;

float exponentialInOut(float t) {
  return t == 0.0 || t == 1.0
    ? t
    : t < 0.5
      ? +0.5 * pow(2.0, (20.0 * t) - 10.0)
      : -0.5 * pow(2.0, 10.0 - (t * 20.0)) + 1.0;
}
float quadraticInOut(float t) {
  float p = 2.0 * t * t;
  return t < 0.5 ? p : -p + (4.0 * t) - 1.0;
}
float customEase (float t) {
   return ((sin( t / 0.49 ) * 1.23) * (abs( t / 2. ) * 1.82));
}

void main() {
    vec3 color = vec3(0.0);

    float pct = abs(sin(u_time));
    float newTime = exponentialInOut(pct);
    //newTime = quadraticInOut (pct);
    newTime = customEase (pct);
    
    color = mix(colorA, colorB, newTime); 

    gl_FragColor = vec4(color,1.0);
}
