!!ver 100 150
!!permu BUMP
!!permu FRAMEBLEND
!!permu SKELETAL
!!permu FOG
!!samps shadowmap diffuse normalmap specular
#include "sys/defs.h"

varying vec2 tcbase;
varying vec3 lightvector;
#if defined(VERTEXCOLOURS)
varying vec4 vc;
#endif
//spec
varying vec3 eyevector;
#ifdef VERTEX_SHADER
#include "sys/skeletal.h"
void main ()
{
	vec3 n, s, t, w;
	gl_Position = skeletaltransform_wnst(w,n,s,t);
	tcbase = v_texcoord; //pass the texture coords straight through
	vec3 lightminusvertex = l_lightposition - w.xyz;
	lightvector.x = dot(lightminusvertex, s.xyz);
	lightvector.y = dot(lightminusvertex, t.xyz);
	lightvector.z = dot(lightminusvertex, n.xyz);
	#if defined(VERTEXCOLOURS)
	vc = v_colour;
	#endif
	//spec
	vec3 eyeminusvertex = e_eyepos - w.xyz;
	eyevector.x = dot(eyeminusvertex, s.xyz);
	eyevector.y = dot(eyeminusvertex, t.xyz);
	eyevector.z = dot(eyeminusvertex, n.xyz);
}
#endif

#ifdef FRAGMENT_SHADER
#include "sys/fog.h"

void main ()
{
float colorscale = max(1.0 - (dot(lightvector, lightvector)/(l_lightradius*l_lightradius)), 0.0);
vec4 bases = texture2D(s_diffuse, tcbase);

#ifdef VERTEXCOLOURS
bases.rgb *= bases.a;
#endif

//bump
vec3 bumps = normalize(vec3(texture2D(s_normalmap, tcbase)) - 0.5);

#ifdef SPECULAR
vec4 specs = texture2D(s_specular, tcbase);
#endif

vec3 diff;
vec3 nl = normalize(lightvector);
diff = bases.rgb * (l_lightcolourscale.x + l_lightcolourscale.y * max(dot(vec3(0.0, 0.0, 1.0), nl), 0.0));

#ifdef SPECULAR
vec3 halfdir = normalize(normalize(eyevector) + nl);
float spec = pow(max(dot(halfdir, bumps), 0.0), 32.0 * specs.a);
diff += l_lightcolourscale.z * spec * specs.rgb;
#endif

#if defined(VERTEXCOLOURS)
diff *= vc.rgb * vc.a;
#endif
gl_FragColor.rgb = fog3additive(diff*colorscale*l_lightcolour);
}
#endif
