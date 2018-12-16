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

void Input_Impulses()
{
	if(gameState == GAME_STATE_RUNNING){
		if(input_impulse){
			inputImpulses = input_impulse;
			inputFireButton = input_buttons & 1;
			switch(inputImpulses){
				case 100:
					Weap_FireTrigger();
				break;
				case 154:
					
				break;
				default:
				break;
			}
		}
	}
}

void Input_Cursor()
{
	switch(gameState){
		case GAME_STATE_MENU:
			inputCursor = TRUE;
			setcursormode(inputCursor);
		break;
		case GAME_STATE_ED:
			if(inputCursor){
				switch(edMode){
					case ED_MODE_SELECT:
						edCursorImg = "textures/ed/cursor.tga";
					break;
					case ED_MODE_MOVE:
						edCursorImg = "textures/ed/move.tga";
					break;
					case ED_MODE_ROTATE:
						edCursorImg = "textures/ed/rotate.tga";
					break;
					case ED_MODE_MESH:
						if(uiPanelMesh == TRUE){
							edCursorImg = "textures/ed/cursor.tga";
						}
						else{
							edCursorImg = "textures/ed/mesh.tga";
						}
					break;
					case ED_MODE_ENT:
						edCursorImg = "textures/ed/char.tga";
					break;
					case ED_MODE_CRUMB:
						edCursorImg = "textures/ed/crumb.tga";
					break;
					default:
						edCursorImg = "";
					break;
				}
			}
			if(inputCursorOrigin_y > UI_HEADER_SAFEZONE){
				setcursormode(inputCursor,edCursorImg);
			}
			else{
				setcursormode(inputCursor,"textures/ed/cursor.tga");
			}
		break;
		case GAME_STATE_PRERUNNING:
			setcursormode(FALSE);
		break;
		case GAME_STATE_RUNNING:
			setcursormode(FALSE);
		break;
		default:
			setcursormode(FALSE);
		break;
	}
}

void Input_Move()
{
	if(gameState == GAME_STATE_ED){
		if(inputCursor == TRUE){
			if(edMode == ED_MODE_MOVE){
				if(inputMouse3Pressed == TRUE){
					Ed_MoveZ();
				}
				else{
					Ed_MoveXY();
				}
			}
		}
		//little pause between a move Z and another, to avoid rough movements
		if(inputCursorMoveBlock == TRUE){
			inputCursorMoveTime++;
			if(inputCursorMoveTime >= 10){
				inputCursorMoveBlock = FALSE;
				inputCursorMoveTime = 0;
			}
		}
	}
}

void Input_CursorDelta()
{
	if(gameState == GAME_STATE_ED){
		if(inputCursor == TRUE){
			if((inputCursorDeltaOld - inputCursorOrigin_y)>0){
				inputCursorDir = 1;
			}
			else if((inputCursorDeltaOld - inputCursorOrigin_y)<0){
				inputCursorDir = 2;
			}
			else{
				inputCursorDir = 0;
			}
		}
	}
}

void Input_CursorDeltaOld()
{
	inputCursorDeltaOld = inputCursorOrigin_y;
}

void Input_ModeTrigger()
{
	if(inputCursorOrigin_y > UI_HEADER_SAFEZONE){
		switch(edMode){
			case ED_MODE_SELECT:
				Ed_Select();
			break;
			case ED_MODE_MOVE:
				Ed_ModeMoveToggle();
			break;
			case ED_MODE_ROTATE:
				Ed_Rotate();
			break;
			case ED_MODE_MESH:
				Ed_ModeMeshOnByClick();
			break;
			case ED_MODE_ENT:
				Ed_PlaceBlank();
			break;
			case ED_MODE_CRUMB:
				Ed_PlaceCrumb();
			break;
			//TEMP
			case ED_MODE_COLLISION:
				if(inputCursorOrigin_x > UI_PREVIEWMODELWIN_SIZE_x){
					Ed_PlaceColEntity();
				}
			break;
		}
	}
}

void Input_ArrowLeftPressed()
{
}

void Input_ArrowRightPressed()
{
}

void Input_CtrlLeftPressed()
{
	if(gameState == GAME_STATE_ED){
		if(viewTop == TRUE){
			viewTopZoom-=32;
			if(viewTopZoom < 32){
				viewTopZoom = 32;
			}
		}
	}
}

void Input_ShiftLeftPressed()
{
	if(gameState == GAME_STATE_ED){
		if(viewTop == TRUE){
			viewTopZoom+=32;
			if(viewTopZoom > 1920){
				viewTopZoom = 1920;
			}
		}
	}
}

void Input_ArrowUpReleased()
{
	if(gameState == GAME_STATE_ED){
		Ed_MeshFolderUp();
	}
}

void Input_ArrowDownReleased()
{
	if(gameState == GAME_STATE_ED){
		Ed_MeshFolderDown();
	}
}

void Input_ArrowLeftReleased()
{
	if(gameState == GAME_STATE_ED){
		Ed_MeshModelDecrement();
	}
}

void Input_ArrowRightReleased()
{
	if(gameState == GAME_STATE_ED){
		Ed_MeshModelIncrement();
	}
}

void Input_EscReleased()
{
	if(gameState == GAME_STATE_ED){
		Ed_Deselect();
		Ed_ModeMeshOff();
	}
}

void Input_SpaceReleased()
{
	if(gameState == GAME_STATE_ED){
		if(uiTimeline == TRUE){
			uiTimelinePlay = !uiTimelinePlay;
		}
	}
}

void Input_EnterReleased()
{
	if(gameState == GAME_STATE_ED){
		if(uiPanelMesh == TRUE){
			Ed_PlaceMesh();
			Ed_ModeMeshOff();
		}
		if(levelSave == TRUE){
			Level_Save();
		}
	}
}

void Input_CtrlLeftReleased()
{
	inputCtrlPressed = FALSE;
	if(gameState == GAME_STATE_ED){
		if(viewTop == FALSE){
			Ed_ElevationDown();
		}
	}
}

void Input_CtrlRightReleased()
{
}

void Input_ShiftLeftReleased()
{
	inputShiftPressed = FALSE;
	if(gameState == GAME_STATE_ED){
		if(viewTop == FALSE){
			Ed_ElevationUp();
		}
	}
}

void Input_MouseButton1Pressed()
{
	inputMouse1Pressed = TRUE;
}

void Input_MouseButton3Pressed()
{
	inputMouse3Pressed = TRUE;
}

void Input_MouseButton2Pressed()
{
	
}

void Input_MouseWheelDownPressed()
{
	
}

void Input_MouseWheelUpPressed()
{
	
}

void Input_MouseButton1Released()
{
	inputMouse1Pressed = FALSE;
	switch(gameState){
		case GAME_STATE_MENU:
			CUI_TriggerButton1Released();
		break;
		case GAME_STATE_ED:
			if(inputCursor == TRUE){
				CUI_TriggerButton1Released();
			}
			//trigger mouse event, but caring of not do stuff while clicking on header buttons..
			if(inputCursorOrigin_y > UI_HEADER_SAFEZONE){
				Input_ModeTrigger();
			}
		break;
		case GAME_STATE_PRERUNNING:
			CUI_TriggerButton1Released();
		break;
		
	}
}

void Input_MouseButton2Released()
{
	if(gameState == GAME_STATE_ED){
		inputCursor = !inputCursor;
	}
}


void Input_MouseButton3Released()
{
	if(gameState == GAME_STATE_ED){
		inputMouse3Pressed = FALSE;
	}
}

void Input_MouseWheelDownReleased()
{
	if(gameState == GAME_STATE_ED){
		if(inputCursor == TRUE){
			if(edMode == ED_MODE_SELECT || edMode == ED_MODE_MOVE || edMode == ED_MODE_ROTATE){
				Ed_GridIncrement();
			}
		}
		else{
			Camera_SpeedIncrement();
		}
	}
}

void Input_MouseWheelUpReleased()
{
	if(gameState == GAME_STATE_ED){
		if(inputCursor == TRUE){
			if(edMode == ED_MODE_SELECT || edMode == ED_MODE_MOVE || edMode == ED_MODE_ROTATE){
				Ed_GridDecrement();
			}
		}
		else{
			Camera_SpeedDecrement();
		}
	}
}

void Input_KeysReleased(float scanx)
{
	//tab
	if (scanx == K_TAB){
		if(gameState == GAME_STATE_ED){
			gameState = GAME_STATE_RUNNING;
		}
		else if(gameState == GAME_STATE_RUNNING){
			gameState = GAME_STATE_ED;
			if(player != world){
				inputCursor = FALSE;
			}
			else{
				UI_Warning("A player entity MUST be created to launch game");
			}
		}
		if(gameState == GAME_STATE_RUNNING){
			
		}
		Util_ResetPlacedPosition(player);
		Ed_Restart();
	}
	//keys released
	if(gameState == GAME_STATE_ED){
		//LETTER A
		if(scanx == 97){
		}
		//LETTER B
		if(scanx == 98){
			//Bsp_PlaneCreate();
		}
		//LETTER C
		if(scanx == 99){
			Ed_ModeChar();
		}
		//LETTER D
		if(scanx == 100 && inputShiftPressed){
			Ed_Duplicate();
		}
		//letter E
		if (scanx == 101){
			Ed_ModeMove();
		}
		//letter F
		if (scanx == 102 && inputShiftPressed){
			Render_ShadingToggle();
		}
		//LETTER G
		if(scanx == 103){
			Ed_Group();
		}
		//LETTER H
		if(scanx == 104){
			Ed_Ungroup();
		}
		//LETTER I
		if(scanx == 105){
			Ed_ModeItem();
		}
		//letter L
		if (scanx == 108){
		}
		//LETTER M
		if(scanx == 109){
			Ed_ModeMeshOnByKey();
		}
		//LETTER N
		if(scanx == 110){
			Bin_Write();
		}
		//letter O
		if (scanx == 111){
			Bin_Read();
		}
		//letter P
		if (scanx == 112){
			Ed_Prefab();
		}
		//letter Q
		if (scanx == 113){
			Ed_ModeSelect();
		}
		//letter R
		if (scanx == 114){
			Ed_ModeRotate();
		}
		//letter S
		if (scanx == 115){
		}
		//letter T
		if (scanx == 116){
			viewTop = !viewTop;
		}
		//letter W
		if (scanx == 119){
			
		}
		//letter X
		if (scanx == 120){
			
		}
		//letter Y
		if (scanx == 121){
		}
		//letter Z
		if (scanx == 122){
			//Shift + z
			if(inputShiftPressed == TRUE){
			}
			//Ctrl +z
			else if(inputCtrlPressed == TRUE){
			}
			//z key
			else{
			}
		}
		//backspace
		if (scanx == K_BACKSPACE){
			Ed_Remove();
		}
	}
}

void Input_KeysReleasedMessageMode(float scanx)
{
	if(gameState == GAME_STATE_ED){
		//LETTER A
		if(scanx == 97){
			uiMessageText = strcat(uiMessageText,"a");
		}
		//LETTER B
		if(scanx == 98){
			uiMessageText = strcat(uiMessageText,"b");
		}
		//LETTER C
		if(scanx == 99){
			uiMessageText = strcat(uiMessageText,"c");
		}
		//LETTER D
		if(scanx == 100){
			uiMessageText = strcat(uiMessageText,"d");
		}
		//LETTER E
		if(scanx == 101){
			uiMessageText = strcat(uiMessageText,"e");
		}
		//LETTER F
		if(scanx == 102){
			uiMessageText = strcat(uiMessageText,"f");
		}
		//LETTER G
		if(scanx == 103){
			uiMessageText = strcat(uiMessageText,"g");
		}
		//LETTER H
		if(scanx == 104){
			uiMessageText = strcat(uiMessageText,"h");
		}
		//LETTER I
		if(scanx == 105){
			uiMessageText = strcat(uiMessageText,"i");
		}
		//LETTER J
		if(scanx == 106){
			uiMessageText = strcat(uiMessageText,"j");
		}
		//LETTER K
		if(scanx == 107){
			uiMessageText = strcat(uiMessageText,"k");
		}
		//letter L
		if (scanx == 108){
			uiMessageText = strcat(uiMessageText,"l");
		}
		//LETTER M
		if(scanx == 109){
			uiMessageText = strcat(uiMessageText,"m");
		}
		//LETTER N
		if(scanx == 110){
			uiMessageText = strcat(uiMessageText,"n");
		}
		//letter O
		if (scanx == 111){
			uiMessageText = strcat(uiMessageText,"o");
		}
		//letter P
		if (scanx == 112){
			uiMessageText = strcat(uiMessageText,"p");
		}
		//letter Q
		if (scanx == 113){
			uiMessageText = strcat(uiMessageText,"q");
		}
		//letter R
		if (scanx == 114){
			uiMessageText = strcat(uiMessageText,"r");
		}
		//letter S
		if (scanx == 115){
			uiMessageText = strcat(uiMessageText,"s");
		}
		//letter T
		if (scanx == 116){
			uiMessageText = strcat(uiMessageText,"t");
		}
		//letter U
		if (scanx == 117){
			uiMessageText = strcat(uiMessageText,"u");
		}
		//letter V
		if (scanx == 118){
			uiMessageText = strcat(uiMessageText,"v");
		}
		//letter W
		if (scanx == 119){
			uiMessageText = strcat(uiMessageText,"w");
		}
		//letter X
		if (scanx == 120){
			uiMessageText = strcat(uiMessageText,"x");
		}
		//letter Y
		if (scanx == 121){
			uiMessageText = strcat(uiMessageText,"y");
		}
		//letter Z
		if (scanx == 122){
			uiMessageText = strcat(uiMessageText,"z");
		}
		//backspace
		if (scanx == K_BACKSPACE){
			uiMessageText = substring(uiMessageText,0,strlen(uiMessageText)-1);
		}
		//enter
		if (scanx == K_ENTER){
			UI_PopupClose();
		}
	}
}

float Input_Manager(float evtype,float scanx,float chary)
{
	switch(evtype){
		case IE_KEYDOWN:
			//mouse buttons pressed
			if (scanx == K_MOUSE1){
				Input_MouseButton1Pressed();
			}
			if (scanx == K_MOUSE2){
			}
			if (scanx == K_MOUSE3){
				Input_MouseButton3Pressed();
			}
			if (scanx == K_MWHEELDOWN){
				Input_MouseWheelDownPressed();
			}
			if (scanx == K_MWHEELUP){
				Input_MouseWheelUpPressed();
			}
			if(scanx == K_LEFTARROW){
				Input_ArrowLeftPressed();
			}
			if(scanx == K_RIGHTARROW){
				Input_ArrowRightPressed();
			}
			if (scanx == K_LCTRL){
				inputCtrlPressed = TRUE;
				Input_CtrlLeftPressed();
			}
			if (scanx == K_LSHIFT){
				inputShiftPressed = TRUE;
				Input_ShiftLeftPressed();
			}
		break;
		case IE_KEYUP:
			//use inputGetScan to identify which code belongs to key pressed (extraordinary useful)
			inputGetScan = scanx;
			//mouse buttons released
			if (scanx == K_MOUSE1){
				Input_MouseButton1Released();
			}
			if (scanx == K_MOUSE2){
				Input_MouseButton2Released();
			}
			if (scanx == K_MOUSE3){
				Input_MouseButton3Released();
			}
			if (scanx == K_MWHEELDOWN){
				Input_MouseWheelDownReleased();
			}
			if (scanx == K_MWHEELUP){
				Input_MouseWheelUpReleased();
			}
			if(scanx == K_LEFTARROW){
				Input_ArrowLeftReleased();
			}
			if(scanx == K_RIGHTARROW){
				Input_ArrowRightReleased();
			}
			if(scanx == K_UPARROW){
				Input_ArrowUpReleased();
			}
			if(scanx == K_DOWNARROW){
				Input_ArrowDownReleased();
			}
			if (scanx == K_ESCAPE){
				Input_EscReleased();
			}
			if(scanx == K_SPACE){
				Input_SpaceReleased();
			}
			if(scanx == K_BACKSPACE){
			}
			if (scanx == K_ENTER){
				Input_EnterReleased();
			}
			if (scanx == K_LCTRL){
				Input_CtrlLeftReleased();
			}
			if (scanx == K_LSHIFT){
				Input_ShiftLeftReleased();
			}
			if (scanx == K_RCTRL){
				Input_CtrlRightReleased();
			}
			if (scanx == K_PGDN){
			}
			//message mode is off, so keyboard letters are used to control editor scene
			if(uiMessageMode == FALSE){
				Input_KeysReleased(scanx);
			}
			//message mode is on, keyboard letters are used to save temporary string uiMessageText
			else{
				Input_KeysReleasedMessageMode(scanx);
			}
		break;
		case IE_MOUSEDELTA:
			inputCursorDelta_x = scanx;
			inputCursorDelta_y = chary;
		break;
		case IE_MOUSEABS:
			inputCursorOrigin_x = scanx;
			inputCursorOrigin_y = chary;		
		return TRUE;
	}
	return FALSE;
}

void Input_Visualize()
{
	if(gameState == GAME_STATE_ED){
		Input_CursorDeltaOld();
	}
}

void Input_PostVisualize()
{
	Input_Cursor();
}