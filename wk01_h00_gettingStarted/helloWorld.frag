#ifdef GL_ES
precision mediump float;
#endif

vec4 red() {
	return vec4(1.0, 0.0, 0.0, 1.0);
}

void main() {
	vec4 color = vec4(vec3(0.1, 1.0, 0.0),1.0); 
	gl_FragColor = vec4(1.0,0.0,1.0,1.0);
	gl_FragColor = red();
	gl_FragColor = color;
}

