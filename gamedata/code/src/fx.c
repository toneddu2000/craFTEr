/*
MIT License

Copyright (c) 2018 Antonio "toneddu2000" Latronico

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

void FX_GlslPostProcessVarsInit()
{
	fxPostprocessDepth = FALSE;
	fxPostprocessColor = FALSE;
	//create sun cvar
	registercvar("sun_intensity","0.2");
	registercvar("sun_height","1000");
	//create camera cvar
	registercvar("camera_speed","0.5");
	//create glsl cvars
	registercvar("glsl_time","0");
	registercvar("glsl_mousex","0");
	registercvar("glsl_mousey","0");
	registercvar("glsl_velx","0");
	registercvar("glsl_vely","0");
	registercvar("glsl_skysize","0.006");
	registercvar("glsl_seasize","0.0006");
	registercvar("glsl_seamove","1");
	registercvar("glsl_bloomthres","0.45");
	registercvar("glsl_bloomintensity","1.2");
}

void FX_GlslPostProcessSetViewProp(float w,float h)
{
	local float sizex = cvar("vid_width");
	local float sizey = cvar("vid_height");
	local vector r = [w,h,0];
	
	//rt shaders to compile. Order matters! Latter will be seen!
	if(fxPostprocessDepth == TRUE){
		setproperty(VF_RT_DEPTH, "ppdepth", 4,r);
		setviewprop(VF_SIZE, r);
	}
	if(fxPostprocessColor == TRUE){
		setproperty(VF_RT_DESTCOLOUR, fxName, 1, r);
		setviewprop(VF_SIZE, r);
	}
}

void FX_GlslPostProcessFlush()
{
	//flush fx or scene won't be rendered
	if(fxPostprocessDepth == TRUE){
		setproperty(VF_RT_DEPTH, "");
	}
	if(fxPostprocessColor == TRUE){
		setproperty(VF_RT_DESTCOLOUR, "");
	}
}

void FX_GlslPostProcessStoreToTexture(float screenwidth,float screenheight)
{
	
	//store postprocess in shader which has $rt: keyword
	if(fxPostprocessColor == TRUE){
		drawpic([0,0,0],fxName,[screenwidth,screenheight,0],[1,1,1],1);
	}
	if(fxPostprocessDepth == TRUE){
		drawpic([0,0,0],"ppdepth",[screenwidth,screenheight,0],[1,1,1],1);
	}
}

void FX_GlslGetUniformByCvars()
{
	//setting vars to cvars, which have uniform corrispective in glsl shader.
	//add time
	fxGlslTimer = time;
	localcmd(strcat("glsl_time ",ftos(fxGlslTimer),"\n"));
	//add mouse position (for motion blur stuff)
	local vector mpos = getmousepos();
	localcmd(strcat("glsl_mousex ",ftos(mpos_x),"\n"));
	localcmd(strcat("glsl_mousey ",ftos(mpos_y),"\n"));
	//add velocity
	localcmd(strcat("glsl_velx ",ftos(player.velocity_x),"\n"));
	localcmd(strcat("glsl_vely ",ftos(player.velocity_y),"\n"));
}

void Fx_GlslInit()
{
	fxName = "ppssao";
	FX_GlslPostProcessVarsInit();
}

void Fx_GlslPostVisualize(float vwidth,float vheight)
{
	FX_GlslPostProcessFlush();
	FX_GlslPostProcessStoreToTexture(vwidth,vheight);
}

void Fx_Init()
{
	Fx_GlslInit();
	fxInjuredTime = 1;
}

void Fx_PlayerInjured(float vwidth,float vheight)
{	
	if(player.entInjured == TRUE){
		fxInjuredTime -= frametime*2;
		drawfill([0,0,0],[vwidth,vheight,0],[1,0,0],fxInjuredTime);
		if(fxInjuredTime <= 0){
			player.entInjured = FALSE;
			fxInjuredTime = 1;
		}
	}
	else{
		fxInjuredTime = 1;
	}
	//(vector position, vector size, vector rgb, float alpha, optional float drawflag) drawfill
	//drawstring([15,15,0],uiWarningText,[vwidth/80,vwidth/80,0],[1,0,0],uiWarningAlpha,0);
}

void Fx_Visualize(float vwidth,float vheight)
{
	FX_GlslPostProcessSetViewProp(vwidth,vheight);
}

void Fx_PostVisualize(float vwidth,float vheight)
{
	Fx_GlslPostVisualize(vwidth,vheight);
	Fx_PlayerInjured(vwidth,vheight);
}