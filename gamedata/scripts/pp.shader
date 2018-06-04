ppcolor
{
	program ton_pp_basic
	{
		map $rt:ppcolor
	}
	{
		map $sourcedepth
	}
	
}

ppdepth
{
	program ton_pp_depth
	{
		map $rt:ppdepth
	}
	{
		map $sourcedepth
	}
}

ppssao
{
	program ton_pp_ssao
	{
		map $rt:ppssao
	}
	{
		map $gbuffer0
	}
}

ppao
{
	program ton_pp_ao
	{
		map $rt:ppao
	}
	{
		map $gbuffer0
	}
}


ppbandw
{
	program ton_pp_ao
	{
		map $rt:ppbandw
	}
}

ppmblur
{
	program ton_pp_motionblur
	{
		map $rt:ppmblur
	}
}

ppchrom
{
	program ton_pp_chromaticaberration
	{
		map $rt:ppchrom
	}
}

ppascii
{
	program ton_pp_ascii
	{
		map $rt:ppascii
	}
}

ppbloom
{
	program ton_pp_bloom
	{
		map $rt:ppbloom
	}
}

ppmedian
{
	program ton_pp_median
	{
		map $rt:ppmedian
	}
}