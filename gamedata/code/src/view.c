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

void View_Visualize()
{
	setviewprop(VF_DRAWWORLD, TRUE);
	switch(gameState){
		case GAME_STATE_MENU:
			setviewprop(VF_ORIGIN,[0,0,0]);
			setviewprop(VF_ANGLES,[0,0,0]);
			setviewprop(VF_DRAWCROSSHAIR,FALSE);
		break;
		case GAME_STATE_ED:
			if(viewTop == TRUE){
				setviewprop(VF_ORIGIN,cameraAttachedOrg+[0,0,viewTopZoom]);
				setviewprop(VF_ANGLES,[90,0,0]);
				setviewprop(VF_PERSPECTIVE,FALSE);
				setviewprop(VF_FOVX,2048+viewTopZoom);
				setviewprop(VF_FOVY,(2048/1.8)+viewTopZoom);
			}
			else{
				setviewprop(VF_ORIGIN,cameraAttachedOrg);
				setviewprop(VF_ANGLES,input_angles);
				setviewprop(VF_PERSPECTIVE,TRUE);
			}
			setviewprop(VF_DRAWCROSSHAIR,FALSE);
			addentities(MASK_ENGINE);
		break;
		case GAME_STATE_PRERUNNING:
			
		break;
		case GAME_STATE_RUNNING:
			setviewprop(VF_ORIGIN,cameraAttachedOrg);
			setviewprop(VF_ANGLES,input_angles);
			setviewprop(VF_PERSPECTIVE,TRUE);
			setviewprop(VF_DRAWCROSSHAIR,TRUE);
			addentities(MASK_ENGINE|MASK_VIEWMODEL);
		break;
	}
}

void View_Init()
{
	viewTop = FALSE;
	viewTopZoom = 512;
}