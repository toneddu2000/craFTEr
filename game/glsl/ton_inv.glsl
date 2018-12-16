!!ver 330
//author: Antonio "toneddu2000" Latronico
//placed under cc0 public domain license
#ifdef VERTEX_SHADER
attribute vec2 v_texcoord;
varying vec2 v_edge;
void main(void)
{
	gl_Position = ftetransform();
	v_edge = v_texcoord.xy;
}
#endif

#ifdef FRAGMENT_SHADER
void main() {
	gl_FragColor.rgb = vec3(1,0,0);
	gl_FragColor.a = 0;
	discard;
}
#endif