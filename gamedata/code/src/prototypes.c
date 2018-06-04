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

//prototypes
void 			Game_Init();
void 			Game_Over();
void 			Game_Restart();
void 			Game_FileCheck();
void 			Game_New();
void 			Game_EditorLaunch();
void			Ed_Init();
float 			Ed_GridSize();
void 			Ed_PlaceMesh();
void 			Ed_ModeMoveOff();
void			Level_Load();
void 			Anim_VisualizeAndSetFrame(entity subject,string framename,float loopflag);
void 			Anim_TimelineFrameVisualize(entity subject);
void 			Player_Prop(entity subject);
void			Ent_HealthSubtract(entity subject,float h);
void			UI_Warning(string s);
void			UI_Message(string s);
void			UI_Popup();
void			UI_PopupClose();
//utils
void			Util_ResetCoords(entity subject) {setorigin(subject,subject.origin);setsize(subject,subject.mins,subject.maxs);setmodel(subject,subject.model);}
void			Util_ResetPlacedPosition(entity subject){if(subject){setorigin(subject,subject.edPlacedOrg);subject.angles = subject.edPlacedAngles;}}
void			Util_ResetSize(entity subject){if(subject != world){setsize(subject,subject.mins,subject.maxs);}}
void			Util_SetOldSolid(entity subject){if(subject!=world){subject.edSolidOld = subject.solid;}}
void			Util_EntityPropCommon(entity subject)
{
	subject.edSelected = FALSE;
	subject.edSelectable = TRUE;
	subject.edPlaceable = TRUE;
	subject.edPlacedOrg = subject.origin;
	subject.levelSaveThis = TRUE;
	subject.edPlacedAngles = subject.angles;
	subject.edLayer = 0;
	subject.edSelectedByType = TRUE;
	subject.edSolidOld = subject.solid;
}