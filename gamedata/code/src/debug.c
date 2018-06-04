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

void Debug_Visualize(float vwidth,float vheight)
{
	local float a = 0.4,m=1;
	local vector col = [1,1,1];
	
	if(cvar("debug_enabled")== 1){
		if(gameState == GAME_STATE_ED){
			
		}
		else if(gameState == GAME_STATE_RUNNING){
			if(player){
				drawstring([15,vheight-15,0],ftos(player.entHealth),UI_FONT_MEDIUM,col,a,m);
				drawstring([15,60,0],strcat("On ground: ",ftos(player.physicsOnGround)," - Trace frac fall", ftos(debugTraceFracFall) ),UI_FONT_BIG,[1,0,0],a,m);
				drawstring([15,100,0],strcat("Trace frac forward", ftos(player.physicsForwardFrac) ),UI_FONT_BIG,[1,0,0],a,m);
				drawstring([15,160,0],strcat("Trace frac step", ftos(player.physicsForwardFrac) ),UI_FONT_BIG,[0,1,0],a,m);
			}
		}
	}
}