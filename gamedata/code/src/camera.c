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

void Camera_Visualize()
{
	//editor
	if(gameState == GAME_STATE_ED){
		cameraAttachedOrg = camera.origin;
	}
	//play mode
	else if(gameState == GAME_STATE_RUNNING){
		if(player){
			if(player.skelEnabled == TRUE){
				cameraAttachedOrg = gettaginfo(player, gettagindex(player,"head"));
			}
			else{
				cameraAttachedOrg = [0,0,0];
			}
		}
	}
}

void Camera_SpeedIncrement()
{
	cameraSpeed += CAMERA_SPEED_INCREMENT;
	if(cameraSpeed > CAMERA_SPEED_MAX){
		cameraSpeed = CAMERA_SPEED_MAX;
	}
}

void Camera_SpeedDecrement()
{
	cameraSpeed -= CAMERA_SPEED_INCREMENT;
	if(cameraSpeed <= 0){
		cameraSpeed = CAMERA_SPEED_MIN;
	}
}

void Camera_Init()
{
	camera = spawn();
	cameraSpeed = CAMERA_SPEED_INIT;
	camera.solid = SOLID_NOT;
	setorigin(camera,[0,0,300]);
	camera.drawmask = MASK_ENGINE;
}