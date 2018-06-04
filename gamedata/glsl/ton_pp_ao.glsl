!!ver 330
//	author: Antonio "toneddu2000" Latronico
//	placed under cc0 public domain license
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
varying vec2 v_edge;
uniform sampler2D s_t0;
float aoReduction = 32.0;
void main(void)
{
	 // sample zbuffer (in linear eye space) at the current shading point	
	float zr = 1.0-texture( s_t0, v_edge.xy ).x;

    // sample neighbor pixels
	float ao = 0.0;
	for( int i=0; i<8; i++ )
	{
        // sample the zbuffer at a neightbor pixel (in a 16 pixel radious)        		
        float z = 1.0-texture( s_t0, (v_edge.xy + floor(2.0)) ).x;
        // accumulate occlusion if difference is less than 0.1 units		
		ao += clamp( (zr-z)/0.1, 0.0, 1.0);
	}
    // average down the occlusion	
    ao = clamp( 1.0 - ao/aoReduction, 0.0, 1.0 );
	
	vec3 col = vec3(ao);
	
    // uncomment this one out for seeing AO with actual image/zbuffer	
	col *= texture( s_t0, v_edge.xy ).xyz;
	
	gl_FragColor = vec4(col,1.0);
}
#endif