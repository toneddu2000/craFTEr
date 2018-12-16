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

void CSQC_Init(float apilevel, string enginename, float engineversion)
{
	Game_Init();	
}

void CSQC_WorldLoaded(){}

noref float CSQC_ConsoleCommand(string cmd){return TRUE;}

float CSQC_InputEvent(float evtype, float scanx, float chary, float devid)
{
	local float i = Input_Manager(evtype,scanx,chary);
	
	return i;
}

void CSQC_Input_Frame()
{
	Input_Impulses();
	Input_CursorDelta();
	Input_Move();
	Physics_PlayerExecute();
}

void CSQC_UpdateView(float vwidth, float vheight, float notmenu)
{
	clearscene();
	Input_Visualize();
	View_Visualize();
	Camera_Visualize();
	Ed_Visualize();
	Render_Visualize();
	Sound_Visualize();
	Weap_Visualize();
	Fx_Visualize(vwidth,vheight);
	renderscene();
	//post-render stuff (ui,glsl,fx,etc.)
	Input_PostVisualize();
	UI_PostVisualize(vwidth,vheight);
	Render_PostVisualize(vwidth,vheight);
	Debug_Visualize(vwidth,vheight);
	Fx_PostVisualize(vwidth,vheight);
	cprint(ftos(uiPanelEntFuncs));
}