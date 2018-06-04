red
{
	surfaceparm nodlight
	program 	ton_flatcolor#RED
	cull none
}

green
{
	surfaceparm nodlight
	program 	ton_flatcolor#GREENLIGHT
	cull none
}

greendark
{
	surfaceparm nodlight
	program 	ton_flatcolor#GREENDARK
	cull none
}

blue
{
	surfaceparm nodlight
	program 	ton_flatcolor#BLUE
	cull none
}

yellow
{
	surfaceparm nodlight
	program 	ton_flatcolor#YELLOW
	cull none
}

white
{
	surfaceparm nodlight
	program 	ton_flatcolor#WHITE
	cull none
}

greydark
{
	surfaceparm nodlight
	program 	ton_flatcolor#GREYDARK
	cull none
}

redtransp
{
	surfaceparm nodlight
	{
		program 	ton_flatcolor#RED
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		alphaFunc GT0
		depthWrite
		rgbGen identity
	}
	{
		rgbGen identity
		blendFunc GL_DST_COLOR GL_ZERO
		depthFunc equal
	}
	cull none
}

greentransp
{
	surfaceparm nodlight
	program 	ton_flatcolor#GREENLIGHT
	cull none
}

yellowtransp
{
	surfaceparm nodlight
	{
		program 	ton_flatcolor#YELLOW
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		alphaFunc GT0
		depthWrite
		rgbGen identity
	}
	{
		rgbGen identity
		blendFunc GL_DST_COLOR GL_ZERO
		depthFunc equal
	}
	cull none
}

pureblack
{
	surfaceparm nodlight
	program 	ton_flatcolor#PUREBLACK
}

invisible
{
	surfaceparm nodlight
	{
		program 	ton_flatcolor#PUREBLACK
		nodraw
		nolightmap
	}
	
}

inv
{
	surfaceparm nodlight
	{
		program 	ton_inv
	}
}

//netradiant stuff..
textures/common/pureblack
{
	surfaceparm nodlight
	program 	ton_flatcolor#PUREBLACK
	cull none
}

textures/common/caulk
{
	surfaceparm nodlight
	program 	ton_flatcolor#GREYDARK
	cull none
}