wall256x256r
{
	program eg_rtlight#VERTEXCOLOURS
	diffusemap textures/gothic/walls/wall256x256r_d.tga
	specularmap textures/gothic/walls/wall256x256r_s.tga
	normalmap textures/gothic/walls/wall256x256r_n.tga
}

gotportal1bk
{
	{
		fte_program ton_lppwall
		map $gbuffer2	//diffuse lighting info
		map $gbuffer3	//specular lighting info
	}
	//this is drawn during the initial gbuffer pass to prepare it
	fte_bemode gbuffer
	{
		{
			fte_program lpp_depthnorm
			tcgen base
		}
	}
	diffusemap textures/gothic/atlasgothic.tga
	cull none
}

gotportal1
{
	{
		{
			deferredlight
			fte_program ton_lppwall#OFFSETMAPPING
			map $gbuffer2
			map $gbuffer3
			map $diffuse
			map $normalmap
			map $specular
		}
		//this is drawn during the initial gbuffer pass to prepare it
		fte_bemode gbuffer
		{
			{
				fte_program lpp_depthnorm
				tcgen base
			}
		}
		
	}
}

gotportal2
{
	program eg_rtlight#VERTEXCOLOURS
	diffusemap textures/gothic/atlasgothic.tga
	cull none
}

doorfake1
{
	program eg_rtlight#VERTEXCOLOURS
	diffusemap textures/gothic/doorfake1.tga
	cull none
}

doorfake2
{
	program eg_rtlight#VERTEXCOLOURS
	diffusemap textures/gothic/doorfake1.tga
	cull none
}

wdet1
{
	program eg_rtlight#VERTEXCOLOURS
	diffusemap textures/gothic/walls/walldet1_d.tga
	specularmap textures/gothic/walls/walldet1_s.tga
	normalmap textures/gothic/walls/walldet1_n.tga
	cull none
}

wall256x128b
{
	program eg_rtlight#VERTEXCOLOURS
	diffusemap textures/gothic/atlasgothic.tga
	specularmap textures/gothic/atlasgothic_s.tga
	normalmap textures/gothic/atlasgothic_n.tga
	cull none
}

wall256x256b
{
	program eg_rtlight#VERTEXCOLOURS
	diffusemap textures/gothic/atlasgothic.tga
	specularmap textures/gothic/atlasgothic_s.tga
	normalmap textures/gothic/atlasgothic_n.tga
	cull none
}

gotwall2_256
{
	program eg_rtlight#VERTEXCOLOURS
	diffusemap textures/gothic/walls/wall2_256.tga
	specularmap textures/gothic/walls/wall2_256_s.tga
	normalmap textures/gothic/walls/wall2_256_n.tga
	cull none
}

gothic/walls/wall2_256
{
	{
		{
			deferredlight
			fte_program ton_lppwall
			map $gbuffer2
			map $gbuffer3
			map $diffuse
			//map $normalmap
			//map $specular
		}
		//this is drawn during the initial gbuffer pass to prepare it
		fte_bemode gbuffer
		{
			{
				fte_program lpp_depthnorm
				tcgen base
			}
		}
		
	}
}

gothic/stairs/stairs1_256
{
	{
		{
			deferredlight
			fte_program ton_lppwall
			map $gbuffer2
			map $gbuffer3
			map $diffuse
			//map $normalmap
			//map $specular
		}
		//this is drawn during the initial gbuffer pass to prepare it
		fte_bemode gbuffer
		{
			{
				fte_program lpp_depthnorm
				tcgen base
			}
		}
		
	}
}

gothic/pillars/column1
{
	{
		{
			deferredlight
			fte_program ton_lppwall
			map $gbuffer2
			map $gbuffer3
			map $diffuse
			//map $normalmap
			//map $specular
		}
		//this is drawn during the initial gbuffer pass to prepare it
		fte_bemode gbuffer
		{
			{
				fte_program lpp_depthnorm
				tcgen base
			}
		}
		
	}
}

gothic/pillars/pillar1
{
	{
		{
			deferredlight
			fte_program ton_lppwall
			map $gbuffer2
			map $gbuffer3
			map $diffuse
			//map $normalmap
			//map $specular
		}
		//this is drawn during the initial gbuffer pass to prepare it
		fte_bemode gbuffer
		{
			{
				fte_program lpp_depthnorm
				tcgen base
			}
		}
		
	}
}

gothic/floors/floor1
{
	{
		{
			deferredlight
			fte_program ton_lppwall#OFFSETMAPPING
			map $gbuffer2
			map $gbuffer3
			map $diffuse
			map $normalmap
			map $specular
		}
		//this is drawn during the initial gbuffer pass to prepare it
		fte_bemode gbuffer
		{
			{
				fte_program lpp_depthnorm
				tcgen base
			}
		}
		
	}
}

gothic/floors/floor2
{
	{
		{
			deferredlight
			fte_program ton_lppwall#OFFSETMAPPING
			map $gbuffer2
			map $gbuffer3
			map $diffuse
			map $normalmap
			map $specular
		}
		//this is drawn during the initial gbuffer pass to prepare it
		fte_bemode gbuffer
		{
			{
				fte_program lpp_depthnorm
				tcgen base
			}
		}
		
	}
}

gothic/ceilings/ceiling1
{
	{
		{
			deferredlight
			fte_program ton_lppwall#OFFSETMAPPING
			map $gbuffer2
			map $gbuffer3
			map $diffuse
			map $normalmap
			map $specular
		}
		//this is drawn during the initial gbuffer pass to prepare it
		fte_bemode gbuffer
		{
			{
				fte_program lpp_depthnorm
				tcgen base
			}
		}
		
	}
}

gothic/stairs/toad
{
	{
		{
			deferredlight
			fte_program ton_lppwall
			map $gbuffer2
			map $gbuffer3
			map $diffuse
			//map $normalmap
			//map $specular
		}
		//this is drawn during the initial gbuffer pass to prepare it
		fte_bemode gbuffer
		{
			{
				fte_program lpp_depthnorm
				tcgen base
			}
		}
		
	}
}