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

//act
void Ed_Group()
{
	local int g,gnum=0;
	//at least one object must be selected to be grouped
	if(edSelectedArray[0] != world){
		//don't incapsulate groups
		if(edSelectedArray[0].gameClass == ENT_CLASS_GROUP){
			UI_Warning(strcat("Group succesfully created with ",itos(gnum)," objects"));
			return;
		}
		edEntity = spawn();
		edGroupIndex++;
		edEntity.edGroupedIndex = edGroupIndex;
		edEntity.solid = SOLID_NOT;
		setorigin(edEntity,edSelectedArray[0].origin);
		setsize(edEntity,[-64,-64,-64],[64,64,64]);
		Util_SetOldSolid(edEntity);
		Util_ResetSize(edEntity);
		for(g = 0 ; g < ED_TOTAL_SELECTED ; g++){
			if(edSelectedArray[g] != world){
				gnum++;
				edEntity.edGroupedEnt[g] = edSelectedArray[g];
				//store children offset relative to parent
				edSelectedArray[g].edParentOffset[g] = edSelectedArray[g].origin - edEntity.origin;
				//edSelectedArray[g].edGroupOffset = edSelectedArray[g].origin - edEntity.origin;
				edSelectedArray[g].edGroupedIndex = edGroupIndex;
				//now entity is child of a group, so it's not selectable until it's ungrouped
				edSelectedArray[g].edSelectable = FALSE;
			}
		}
		UI_Message(strcat("Group succesfully created with ",itos(gnum)," objects"));
		//group props
		edEntity.gameClass = ENT_CLASS_GROUP;
		edEntity.edSelectable = TRUE;
		edEntity.edSelectedByType = TRUE;
		edEntity.levelSaveThis = TRUE;
		//TONEDDUFIXME: temp - remove when add layers and selectbytype
		//edEntity.drawmask = MASK_ENGINE;
		edEntity.edLayer = 0;
	}
}

void Ed_Ungroup()
{
	local int i,j=0;
	
	if(edSelectedArray[0] != world){
		if(edSelectedArray[0].gameClass == ENT_CLASS_GROUP){
			for(i = 0 ; i < ED_TOTAL_SELECTED ; i++){
				if(edSelectedArray[0].edGroupedEnt[i] != world){
					j++;
					edSelectedArray[0].edGroupedEnt[i].edParentOffset[i] = [0,0,0];
					edSelectedArray[0].edGroupedEnt[i].edGroupedIndex = 0;
					edSelectedArray[0].edGroupedEnt[i].edSelectable = TRUE;
					edSelectedArray[0].edGroupedEnt[i].solid = edSelectedArray[0].edGroupedEnt[i].edSolidOld;
					Util_ResetSize(edSelectedArray[0].edGroupedEnt[i]);					
				}
			}
			remove(edSelectedArray[0]);
			UI_Message(strcat("Group succesfully ungrouped in ",ftos(j)," entities"));
		}
		else{
			UI_Warning("No group selected");
			return;
		}
	}
}

void Ed_Remove()
{
	local int i,j;
	
	for(i=0;i<ED_TOTAL_SELECTED;i++){
		if(edSelectedArray[i] != world){
			if(edSelectedArray[i].gameClass == ENT_CLASS_PLAYER){
				UI_Warning("Player entity cannot be removed from level");
			}
			if(edSelectedArray[i].gameClass == ENT_CLASS_GROUP){
				for(j=0;j<ED_TOTAL_SELECTED;j++){
					if(edSelectedArray[i].edGroupedEnt[j] != world){
						remove(edSelectedArray[i].edGroupedEnt[j]);
					}
				}
			}
			else if(edSelectedArray[i].gameClass == ENT_CLASS_MESH){
				for(j=0;j<ED_TOTAL_SELECTED;j++){
					if(edSelectedArray[i].edCollisionChildren[j] != world){
						remove(edSelectedArray[i].edCollisionChildren[j]);
					}
				}
			}
			else if(edSelectedArray[i].gameClass == ENT_CLASS_NPC){
				/*
				local entity e[EN_CRUMB_TOTAL];
				if(edSelectedArray[i].crumbFirst != world){
					e[0] = edSelectedArray[i].crumbFirst;
					if(edSelectedArray[i].crumbFirst.crumbNext != world){
						for(j=0;j<EN_CRUMB_TOTAL;j++){
							if(edSelectedArray[i].crumbFirst.crumbNext != world){
								e[j] = edSelectedArray[i].crumbFirst.crumbNext;
							}
						}
					}
				}
				for(j=0;j<EN_CRUMB_TOTAL;j++){
					if(e[j] != world){
						remove(e[j]);
					}
				}
				remove(edSelectedArray[i].crumbFirst);
				remove(edSelectedArray[i].crumbLast);
				*/
			}
			remove(edSelectedArray[i]);
		}
	}
	//clear selection to avoid "zombie" entities manipulation
	Ed_Deselect();
}

void Ed_Duplicate()
{
	local int i;
	for(i=0;i<ED_TOTAL_SELECTED;i++){
		if(edSelectedArray[i] != world){
			if(edSelectedArray[i].gameClass == ENT_CLASS_PLAYER){
				UI_Warning("Player entity cannot be duplicated");
				return;
			}
		}
	}
	//TONEDDUFIXME:for now, just first selected ent is dupl. Would it be better to add array?
	if(edSelectedArray[0] != world){
		edEntity = spawn();
		copyentity(edSelectedArray[0],edEntity);
		edEntity.edSelected = FALSE;
		Util_SetOldSolid(edEntity);
		Util_ResetSize(edEntity);
		//deselect old selection
		Ed_Deselect();
		//duplicated entity is selected and ready to be moved
		edEntity.edSelected = TRUE;
		edSelectedArray[0] = edEntity;
		setorigin(edEntity,inputCursor3dOrg);
		edMode = ED_MODE_MOVE;
		inputMove = TRUE;
		Ed_MoveXY();
	}
}

void Ed_Prefab()
{
	local int i,num=0;
	local float f;
	local string entdat,s="pippo";
	
	if(edSelectedArray[0] != world){
		f = fopen(strcat("prefabs/",s,".prefab"), FILE_WRITE);
		for(i = 0; i < ED_TOTAL_SELECTED; i++){
			if(edSelectedArray[i] != world){
				if(edSelectedArray[i].levelSaveThis == TRUE){
					num++;
					entdat = generateentitydata(edSelectedArray[i]);
					fputs(f,entdat,"\n");
				}	
			}
		}
		fclose(f);
		UI_Message( strcat("Prefab succesfully created with ",ftos(num)," elements") );
	}
}