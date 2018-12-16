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

//mode
void Ed_ModeMoveToggle()
{
	inputMove = !inputMove;
}

void Ed_ModeMoveOff()
{
	inputMove = FALSE;
}

void Ed_ModeMeshOnByClick()
{
	inputTemp3dOrg = inputCursor3dOrg;
	uiPanelMesh = TRUE;
	Ed_MeshFlatLight();
}

void Ed_ModeMeshOnByKey()
{	
	inputTemp3dOrg = inputCursor3dOrg;
	edMode = ED_MODE_MESH;
	uiPanelMesh = TRUE;
	Ed_MeshFlatLight();
}

void Ed_ModeMeshOff()
{
	if(uiPanelMesh == TRUE){
		cvar_set("render_shadeless",ftos(renderShadingToggle));
		uiPanelMesh = FALSE;
		edMode = ED_MODE_SELECT;
	}
}

void Ed_ModeSelect(){edMode = ED_MODE_SELECT;}

void Ed_ModeMove(){edMode = ED_MODE_MOVE;}

void Ed_ModeRotate(){edMode = ED_MODE_ROTATE;}

void Ed_ModeMesh(){edMode = ED_MODE_MESH;}

void Ed_ModeChar(){edMode = ED_MODE_ENT;}

void Ed_ModeItem(){edMode = ED_MODE_ITEM;}

void Ed_ModeCrumb(){edMode = ED_MODE_CRUMB;}

void Ed_ModeLevelSave(){levelSave = TRUE;UI_Popup();}

void Ed_ModeLevelOpen()
{
	//uiMessageText = uiElListLevel.cuiListTextArray[uiElListLevel.cuiListTextIndex];UI_Message(strcat("Level ",uiMessageText," opened successfully"));
	uiListText = uiElListLevel.cuiListTextArray[uiElListLevel.cuiListIndex];
	Level_Load();
	levelOpen = FALSE;
}

void Ed_ModeLevelOpenOn()
{
	levelOpen = TRUE;
}

void Ed_ModeLevelOpenOff()
{
	levelOpen = FALSE;
}

void Ed_ModeLayerToggle()
{
	edLayerArray[uiElListLayer.cuiListIndex].edLayerActive = !edLayerArray[uiElListLayer.cuiListIndex].edLayerActive;
}

void Ed_ModeLayerOn()
{
	edLayerOpen = TRUE;
}

void Ed_ModeLayerOff()
{
	edLayerOpen = FALSE;
}

void Ed_ModeLayerAddObj()
{
	local int i,j=0;
	
	if(edSelectedArray[0] != world){
		for(i=0;i<ED_TOTAL_SELECTED;i++){
			if(edSelectedArray[i] != world){
				edSelectedArray[i].edLayer = uiElListLayer.cuiListIndex;
				j++;
			}
		}
		UI_Message(strcat(itos(j)," elements added to layer ",edLayerNameArray[uiElListLayer.cuiListIndex]));
	}
}

void Ed_ModeSelByTypeOn()
{
	edSelByTypeOpen = TRUE;
}

void Ed_ModeSelByTypeOff()
{
	edSelByTypeOpen = FALSE;
}

void Ed_ModePrefabOn()
{
	edPrefabOpen = TRUE;
}

void Ed_ModePrefabOff()
{
	edPrefabOpen = FALSE;
}

void Ed_ModePrefabLoad()
{
	local entity e;
	local float file,offset;
	local int i=0;
	local string contentdata;
	
	uiListText = uiElListPrefab.cuiListTextArray[uiElListPrefab.cuiListIndex];
	file = fopen(strcat("prefabs/",uiListText,".prefab"), FILE_READNL);
	edEntity = spawn();
	edEntity.gameClass = ENT_CLASS_PREFAB;
	setorigin (edEntity,[0,0,64]);
	edEntity.solid = SOLID_BBOX;
	setsize(edEntity,[-32,-32,-32],[32,32,32]);
	Util_EntityPropCommon(edEntity);
	Util_ResetSize(edEntity);
	//prefab exists
	if (file >= 0){
		contentdata = fgets(file);
		offset = 0;
		fclose(file);
		//(by Spike)
		while ((offset=parseentitydata((e=spawn()), contentdata, offset))){
			//if its from a different map / version of the mod / etc, make sure its modelindex is still correct for its model.
			if (e.model != ""){
				setmodel(e, e.model);
			}
			//make sure it's linked
			else{
				setorigin(e, edEntity.origin);
			}
			edEntity.edGroupedEnt[i] = e;
			edEntity.edGroupedEnt[i].edParentOffset[i] = edEntity.edGroupedEnt[i].origin - edEntity.origin;
			e.edSelected = FALSE;
			i++;
		}
		//last one failed to parse but we had already created an ent for it.
		remove(e);
	}
	//level doesn't exist
	else{
		UI_Warning(strcat("Prefab ",uiListText," doesn't exist"));
		uiListText = "";
		return;
	}
	UI_Message(strcat("Prefab ",uiListText," opened successfully"));
	uiListText = "";
}

void Ed_ModeColResetOrg()
{
	local int i;
	
	for(i=0;i<ED_TOTAL_SELECTED;i++){
		if(edSelectedArray[i] != world){
			setorigin(edSelectedArray[i],[0,0,0]);
			Util_ResetSize(edSelectedArray[i]);
		}
	}
}

void Ed_ModeCollIncreaseX()
{
	if(edSelectedArray[0] != world && edSelectedArray[0].gameClass == ENT_CLASS_MESHCOLLISION){
		setsize(edSelectedArray[0],[edSelectedArray[0].mins_x,edSelectedArray[0].mins_y,edSelectedArray[0].mins_z],[edSelectedArray[0].maxs_x+32,edSelectedArray[0].maxs_y,edSelectedArray[0].maxs_z]);
	}
}

void Ed_ModeCollDecreaseX()
{
	if(edSelectedArray[0] != world && edSelectedArray[0].gameClass == ENT_CLASS_MESHCOLLISION){
		setsize(edSelectedArray[0],[edSelectedArray[0].mins_x,edSelectedArray[0].mins_y,edSelectedArray[0].mins_z],[edSelectedArray[0].maxs_x-32,edSelectedArray[0].maxs_y,edSelectedArray[0].maxs_z]);
	}
}

void Ed_ModeCollIncreaseY()
{
	if(edSelectedArray[0] != world && edSelectedArray[0].gameClass == ENT_CLASS_MESHCOLLISION){
		setsize(edSelectedArray[0],[edSelectedArray[0].mins_x,edSelectedArray[0].mins_y,edSelectedArray[0].mins_z],[edSelectedArray[0].maxs_x,edSelectedArray[0].maxs_y+32,edSelectedArray[0].maxs_z]);
	}
}

void Ed_ModeCollDecreaseY()
{
	if(edSelectedArray[0] != world && edSelectedArray[0].gameClass == ENT_CLASS_MESHCOLLISION){
		setsize(edSelectedArray[0],[edSelectedArray[0].mins_x,edSelectedArray[0].mins_y,edSelectedArray[0].mins_z],[edSelectedArray[0].maxs_x,edSelectedArray[0].maxs_y-32,edSelectedArray[0].maxs_z]);
	}
}

void Ed_ModeCollIncreaseZ()
{
	if(edSelectedArray[0] != world && edSelectedArray[0].gameClass == ENT_CLASS_MESHCOLLISION){
		setsize(edSelectedArray[0],[edSelectedArray[0].mins_x,edSelectedArray[0].mins_y,edSelectedArray[0].mins_z],[edSelectedArray[0].maxs_x,edSelectedArray[0].maxs_y,edSelectedArray[0].maxs_z+32]);
	}
}

void Ed_ModeCollDecreaseZ()
{
	if(edSelectedArray[0] != world && edSelectedArray[0].gameClass == ENT_CLASS_MESHCOLLISION){
		setsize(edSelectedArray[0],[edSelectedArray[0].mins_x,edSelectedArray[0].mins_y,edSelectedArray[0].mins_z],[edSelectedArray[0].maxs_x,edSelectedArray[0].maxs_y,edSelectedArray[0].maxs_z-32]);
	}
}

//timeline
void Ed_ModeTimelineMenuOn()
{
	uiTimelineMenu = TRUE;
}

void Ed_ModeTimelineMenuOff()
{
	uiTimelineMenu = FALSE;
}

void Ed_ModeTimelineOn()
{
	uiTimelineMenu = FALSE;
	//add here setmodel to uiTimelineModel based on uiTimelineIndex
	setmodel(uiTimelineModel,uiElListTimelineMeshes.cuiListTextArray[uiElListTimelineMeshes.cuiListIndex]);
	setsize(uiTimelineModel,uiTimelineModel.mins,uiTimelineModel.maxs);
	uiTimeline = TRUE;
}

void Ed_ModeTimelineOff()
{
	uiTimeline = FALSE;
}

void Ed_ModeTimelineFrameIncrease()
{
	uiTimelineFrameIndex++;
}

void Ed_ModeTimelineFrameDecrease()
{
	if(uiTimelineFrameIndex > 0){
		uiTimelineFrameIndex--;
	}
}

void Ed_ModeTimelineSpeedIncrease()
{
	if(uiTimelineSpeed < 2){
		uiTimelineSpeed+=0.25;
	}
}

void Ed_ModeTimelineSpeedDecrease()
{
	if(uiTimelineSpeed > 0){
		uiTimelineSpeed-=0.25;
	}
}

void Ed_ModeTimelineAddEvent()
{
	//.float 	animEvTime[ANIM_EV_TOTAL],animEvFrame[ANIM_EV_TOTAL];
	//.string	animEvName[ANIM_EV_TOTAL];
	//werewolf.iqm_idle.event
	//example .event
	/*
		evtime:0.6200000
		evname:myfunc
		evfrm:0
	*/
	
	//example .event2
	/*
		modfrm0_evtime:0.6200000
		modfrm0_evname:myfunc
		//comment
		modfrm1_evtime:0.1500000
		modfrm1_evname:myfunc4
		//etc.
	*/
	/*
		
		Anim_EvLoadEvent(entity subject)
		{
			for(i=0;i<ED_EV_TOTAL;i++){
				if (exist for selected entity/model/frame an .event file){
					if(frametoname(subject.modelindex,i)!= ""){
						open selectedmodel_selectedframe.event file
						//store vars
						subject.animEvTime[i]=evtime,subject.animEvName[i]=evname,subject.animEvFrame[i]=evfr
						close file
					}
				}
			}
		}
		
		Anim_EvRun(entity subject)
		{
			if(subject.edEvFrame[subject.frame] != 0){
				if(subject.edEvTime != 0){
					if(subject.edEvTime == subject.animTime){
						En_EvExecute(subject,subject.edEvName);
					}
				}
			}
		}
		
		Anim_EvExecute(entity subject,string funcname)
		{
			callfunction(funcname);
			//subject.nexthink = time + 0.01;
			subject.think();
		}
		
		Anim_EvSaveEvent(entity subject)
		{
			local float f;
			f = fopen(strcat("animevent/",subject.model,"_",ftos(subject.frame),".event"), FILE_WRITE);
			while ((levelEntity = nextent(levelEntity))){
				if(levelEntity.levelSaveThis == TRUE){
					entdat = generateentitydata(levelEntity);
					fputs(f,entdat,"\n");
				}
			}
			fclose(f);
		}
	*/
}