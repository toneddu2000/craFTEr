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
	float al=0.35f;
	
	#ifdef GREENLIGHT
		gl_FragColor.rgb = vec3(0.248,0.840,0.293);
		al = 0.2f;
	#endif
	#ifdef GREENDARK
		gl_FragColor.rgb = vec3(0.115,0.390,0.136);
	#endif
	#ifdef AZURE
		gl_FragColor.rgb = vec3(0.666,0.823,0.912);
	#endif
	#ifdef RED
		gl_FragColor.rgb = vec3(0.910,0.081,0.116);
		al = 0.2f;
	#endif
	#ifdef GREEN
		gl_FragColor.rgb = vec3(0,0.9,0.1);
		al = 0.2f;
	#endif
	#ifdef BLUE
		gl_FragColor.rgb = vec3(0,0.1,0.9);
		al = 0.2f;
	#endif
	#ifdef BLUEGROUP
		gl_FragColor.rgb = vec3(0,0.1,0.9);
		al = 0.5f;
	#endif
	#ifdef YELLOW
		gl_FragColor.rgb = vec3(0.5,0.5,0);
		al = 0.2f;
	#endif
	#ifdef WHITE
		gl_FragColor.rgb = vec3(1,1,1);
	#endif
	#ifdef REDOPAQUE
		gl_FragColor.rgb = vec3(0.910,0.081,0.116);
		al = 1f;
	#endif
	#ifdef GREYDARK
		gl_FragColor.rgb = vec3(0.330,0.340,0.340);
	#endif
	#ifdef PUREBLACK
		gl_FragColor.rgb = vec3(0,0,0);
		al = 1;
	#endif
	//entity custom defines
	#ifdef GRIDLINES
		gl_FragColor.rgb = vec3(0.15,0.15,0.15);
	#endif
	gl_FragColor.a = al;
	if(al<=0){
		discard;
	}
}
#endif